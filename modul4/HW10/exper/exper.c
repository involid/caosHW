#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#define FUSE_USE_VERSION 30
#define _GNU_SOURCE

#include <errno.h>
#include <fuse3/fuse.h>
#include <zip.h>

FILE* x;

#define MAX_PATH 4097
char path_to_zip[MAX_PATH];
zip_t* zip_pointer;
// Callback for stat syscall
int fuse_stat(const char* path, struct stat* st, struct fuse_file_info* fi)
{
    //fprintf(x, "%s\n", path);

    // root
    if (strcmp(path, "/") == 0) {
        st->st_mode = 0555 | S_IFDIR;
        return 0; 
    }

    ++path;
    char buff[MAX_PATH];
    bzero(buff, MAX_PATH);
    strcpy(buff, path);
    struct zip_stat zs;
    int rv_file = zip_stat(zip_pointer, buff, 0, &zs);
    if (rv_file != 0) {
        buff[strlen(buff)] = '/';
        int rv_dir = zip_stat(zip_pointer, buff, 0, &zs);
        if (rv_dir != 0) {
            return -ENOENT;
        }
        st->st_mode = 0555 | S_IFDIR;
    }
    else {
        st->st_mode = 0444 | S_IFREG;
    }
    st->st_size = zs.size;
    st->st_mtime = zs.mtime;
    return 0;
}

// Callback for readdir syscall
int fuse_readdir(
    const char* path,
    void* out,
    fuse_fill_dir_t filler,
    off_t off,
    struct fuse_file_info* fi,
    enum fuse_readdir_flags flags)
{
    //fprintf(x, "\n\npath name is %s\n", path);
    // Directory and its parent
    filler(out, ".", NULL, 0, 0);
    filler(out, "..", NULL, 0, 0);
    ++path;
    int count = zip_get_num_files(zip_pointer);
    for (int i = 0; i < count; ++i) {
        const char *name = zip_get_name(zip_pointer, i, 0);
        char* chk = strstr(name, path);
        if (chk != name) {
            continue;
        }
        struct stat st;
        if (name[strlen(name) - 1] == '/') {
            //subdirectory or directory itself
            if (strlen(name) == strlen(path) + 1) {
                continue;
            }
            const char* other;
            while ((other = zip_get_name(zip_pointer, ++i, 0))) {
                if (other != strstr(other, name)) {
                    --i;
                    break;
                }
            }
        }
        char buff[MAX_PATH];
        bzero(buff, MAX_PATH);
        strcpy(buff, name + strlen(path));
        if (buff[strlen(buff) - 1] == '/') {
            buff[strlen(buff) - 1] = '\0';
        }
        if (strcmp(path, "") == 0) {
            //fprintf(x, "vatafak mazafak  %s\n", buff);
            filler(out, buff, NULL, 0, 0);
        }
        else {
            //fprintf(x, "vatafak mazafak  %s\n", buff + 1);
            filler(out, buff + 1, NULL, 0, 0);
        }
    }
    return 0;
}

// Callback for read syscall
int fuse_read(
    const char* path,
    char* out,
    size_t size,
    off_t off,
    struct fuse_file_info* fi)
{
    fprintf(x, "%s\n", path);
    ++path;
    zip_file_t* zfp = zip_fopen(zip_pointer, path, 0);
    int rv = 0;
    if (zfp == NULL) {
        rv = -ENOENT;
    }
    else if (zip_fseek(zfp, off, SEEK_SET) != 0) {
        rv = -1;
    }
    else {
        rv = zip_fread(zfp, out, size);
    }

    return rv;
}

// Callbacks for FUSE daemon
struct fuse_operations callbacks = {
    .readdir = fuse_readdir,
    .getattr = fuse_stat,
    //.open = fuse_open,
    .read = fuse_read,
};

// Struct for storing user-specified args
typedef struct {
    char* src;
} fuse_options_t;

int main(int argc, char* argv[])
{
    x = fopen("x.txt", "w");
    // Preprocess arguments for FUSE daemon
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    // Prepare fuse_options_t object
    fuse_options_t fuse_options;
    memset(&fuse_options, 0, sizeof(fuse_options));

    // Define patterns
    struct fuse_opt opt_specs[] = {
        {"--src %s", offsetof(fuse_options_t, src), 0}, {NULL, 0, 0}};

    // Find patterns in {argc, argv} and remove them from it
    fuse_opt_parse(&args, &fuse_options, opt_specs, NULL);

    char* res = realpath(fuse_options.src, path_to_zip);
    if (res == NULL) {
        fprintf(stderr, "zip file %s does not exist", fuse_options.src);
    }

    int error;
    zip_pointer = zip_open(path_to_zip, ZIP_RDONLY, &error);
    if (zip_pointer == NULL) {
        fprintf(stderr, "error while opening %s zip file", fuse_options.src);
    }

    //struct zip_stat zs;
    //int rv = zip_stat(zip_pointer, "A", 0, &zs);
    //printf("%d \n", rv);

    //Run FUSE daemon
    int fuse_main_result = fuse_main(args.argc, args.argv, &callbacks, NULL);
    zip_close(zip_pointer);
    fclose(x);
    return fuse_main_result;
}