#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <libgen.h>

const ssize_t symlink_prefix_sz = 8;
const char symlink_prefix[8] = "link_to_";

bool file_exists(char * path) {
    struct stat st;
    return (stat(path, &st) == 0);
}

bool is_symlink(char * path) {
    struct stat st;
    lstat(path, &st);
    return S_ISLNK(st.st_mode);
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

int main(int argc, char* argv[]) {
    printf(basename("/home/involid/mhernoc/caosHW/clang-format"));
}