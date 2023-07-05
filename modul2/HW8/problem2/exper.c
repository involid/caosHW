#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static const int BUFFER_SIZE = 4096;

int main(int argc, char *argv[]) {
    int a[7];
    a[0] = 6;
    a[1] = 2;
    a[2] = 3;
    a[3] = 7;
    a[4] = 3;
    int fd = open("seroj.txt", O_RDONLY);
    struct stat st;
    fstat(fd, &st);
    printf("%d\n", st.st_size);
    close(fd);
    return 0;
}