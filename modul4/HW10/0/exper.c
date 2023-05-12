#include <fcntl.h>
#include <stdio.h>
int main() {
    int fd = open("mnt/hello.txt", O_RDONLY);
    perror("hihi");
}