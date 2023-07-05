#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static const int BUFFER_SIZE = 4096;

int main(int argc, char *argv[]) {
    int fd = open("hot_seroj", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    int a[1234];
    int j = 0;
    for (int i = 12; i > -6; --i) {
        a[j] = i;
        ++j;
    }
    a[0] = 12345;
    a[9] = -434;
    a[10] = 0;
    a[13] = 0;
    write(fd, (char *)a, j * sizeof(int));
    close(fd);
    return 0;
}