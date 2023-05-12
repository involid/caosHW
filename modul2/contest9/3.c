#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

const ssize_t symlink_prefix_sz = 8;
const char symlink_prefix[9] = "link_to_\0";

bool file_exists(char * path) {
    struct stat st;
    return (stat(path, &st) == 0);
}

bool is_symlink(char * path) {
    struct stat st;
    lstat(path, &st);
    return S_ISLNK(st.st_mode);
}

bool is_reg(char * path) {
    struct stat st;
    lstat(path, &st);
    return S_ISREG(st.st_mode);
}

void make_symlink_name(char * src, char * dest) {
    for (int i = 0; i < symlink_prefix_sz; ++i) {
        dest[i] = symlink_prefix[i];
    }
    int i = 0;
    while (src[i] != '\0') {
        dest[i + symlink_prefix_sz] = src[i];
        ++i;
    }
}

int main() {
    char filepath[PATH_MAX];
    char end_line[1];
    while (scanf("%[^\n]", filepath) != EOF) {
        struct stat st;
        //if(lstat(filepath, &st) == 0) {
            if (S_ISLNK(st.st_mode)) {
                char buff[PATH_MAX];
                memset(buff, 0, PATH_MAX);
                realpath(filepath, buff);
                printf("%s\n", buff);
            }
            else if (S_ISREG(st.st_mode)) {
                char buff[PATH_MAX + symlink_prefix_sz];
                memset(buff, 0, PATH_MAX + symlink_prefix_sz);
                make_symlink_name(filepath, buff);
                symlink(filepath, buff);
            }
        //}
        memset(filepath, 0, PATH_MAX);
        scanf("%c", end_line);
    }
}