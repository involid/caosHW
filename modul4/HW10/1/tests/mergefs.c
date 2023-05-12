#include <time.h>
#define FUSE_USE_VERSION 30
#define _GNU_SOURCE

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse3/fuse.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH 4097

char** path_to_dirs;
size_t dirs_num = 0;

void get_path(const char* path, size_t dir_index, char* buff)
{
    bzero(buff, MAX_PATH);
    strcpy(buff, path_to_dirs[dir_index]);
    strcat(buff, "/");
    strcat(buff, path);
}

int get_stat(const char* path, size_t dir_index, struct stat* st)
{
    char buff[MAX_PATH];
    get_path(path, dir_index, buff);
    bzero(st, sizeof(struct stat));
    return stat(buff, st);
}

int newests_mdate(const char* path)
{
    struct timespec tm;
    int inode = -1;
    for (size_t i = 0; i < dirs_num; ++i) {
        struct stat st;
        if (get_stat(path, i, &st) != 0) {
            continue;
        }
        if (inode == -1 || (st.st_mtim.tv_sec > tm.tv_sec ||
                            (st.st_mtim.tv_sec == tm.tv_sec &&
                             st.st_mtim.tv_nsec > tm.tv_nsec))) {
            tm.tv_sec = st.st_mtim.tv_sec;
            tm.tv_nsec = st.st_mtim.tv_nsec;
            inode = st.st_ino;
        }
    }
    return inode;
}

// Callback for stat syscall
int fuse_stat(const char* path, struct stat* st, struct fuse_file_info* fi)
{
    int inode = newests_mdate(path);
    if (inode == -1) {
        return -ENOENT;
    }
    for (size_t i = 0; i < dirs_num; ++i) {
        struct stat stat_buff;
        int rv = get_stat(path, i, &stat_buff);

        if (rv == 0 && (stat_buff.st_ino == inode)) {
            if (S_ISDIR(stat_buff.st_mode)) {
                st->st_mode = 0555 | S_IFDIR;
            }
            else {
                st->st_mode = S_IFREG | 0444;
                st->st_size = stat_buff.st_size;
                st->st_mtime = stat_buff.st_mtime;
            }
            return 0;
        }
    }
    return -1;
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
    // Directory and its parent
    filler(out, ".", NULL, 0, 0);
    filler(out, "..", NULL, 0, 0);

    bool found = false;

    for (int i = 0; i < dirs_num; ++i) {
        char buff[MAX_PATH];
        get_path(path, i, buff);

        DIR* dirp = opendir(buff);
        if (dirp == NULL) {
            continue;
        }

        found = true;
        struct dirent* entry;
        while ((entry = readdir(dirp)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char buff[MAX_PATH];
            bzero(buff, MAX_PATH);
            strcpy(buff, path);
            strcat(buff, "/");
            strcat(buff, entry->d_name);

            struct stat st;
            get_stat(buff, i, &st);
            int inode = newests_mdate(buff);
            if (inode == st.st_ino) {
                filler(out, entry->d_name, NULL, 0, 0);
            }
        };
        closedir(dirp);
    }
    if (!found) {
        return -ENOENT;
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
    int inode = newests_mdate(path);
    if (inode == -1) {
        return -ENOENT;
    }
    for (int i = 0; i < dirs_num; ++i) {
        struct stat st;
        get_stat(path, i, &st);
        if (st.st_ino == inode) {
            char buff[MAX_PATH];
            get_path(path, i, buff);
            FILE* fp = fopen(buff, "r");
            int rv = 0;
            if (fseek(fp, off, SEEK_SET) != 0)
                rv = -1;
            else { 
                rv = fread(out, 1, size, fp);
                fclose(fp);
            }
            return rv;
        }
    }
    return -1;
}

// Callback for open syscall
int fuse_open(const char* path, struct fuse_file_info* fi) {
    // If search failed
    int inode = newests_mdate(path);
    if (inode == -1) {
        return -ENOENT;
    }

    // Files can be opened only for read
    if (O_RDONLY != (fi->flags & O_ACCMODE)) {
        return -EACCES;
    }

    return 0;
}

// Callbacks for FUSE daemon
struct fuse_operations callbacks = {
    .readdir = fuse_readdir,
    .getattr = fuse_stat,
    .open    = fuse_open,
    .read    = fuse_read,
};

// Struct for storing user-specified args
typedef struct {
    char* src;
} fuse_options_t;

int main(int argc, char* argv[])
{
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

    char *pch = strchr(fuse_options.src,':');
    while (pch!=NULL) {
        ++dirs_num;
        pch=strchr(pch+1,':');
    }
    path_to_dirs = calloc(dirs_num, sizeof(char*));
    dirs_num = 0;
    //parsing directory paths
    fuse_options.src = strtok(fuse_options.src, ":");
    while (fuse_options.src != NULL) {
        path_to_dirs[dirs_num] = calloc(MAX_PATH, sizeof(char));
        char* res = realpath(fuse_options.src, path_to_dirs[dirs_num]);
        if (res == NULL) {
            printf("%s  directory does not exist", fuse_options.src);
            return 1;
        }
        ++dirs_num;
        fuse_options.src = strtok(NULL, ":");
    }

    //Run FUSE daemon
    int fuse_main_result = fuse_main(args.argc, args.argv, &callbacks, NULL);
    for (int i = 0; i < dirs_num; ++i) {
        free(path_to_dirs[i]);
    }
    free(path_to_dirs);
    return fuse_main_result;
}