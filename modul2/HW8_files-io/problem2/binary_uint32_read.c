#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static const int BUFFER_SIZE = 4096;

int main(int argc, char *argv[]) {
    char buff[BUFFER_SIZE];
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("THE FILE DOES NOT EXIST !!!\n");
        return 0;
    }
    while(1) {
        int readed = read(fd, buff, BUFFER_SIZE);
        if (readed == 0) break;
        for (int i = 0 ; i < readed / sizeof(int); ++i) {
            printf("%d\n", ((int*)buff)[i]);
        }
    }
    close(fd);
    return 0;
}