#include <sys/mman.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

const ssize_t item_sz = sizeof(struct Item);

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDONLY);
    struct stat st;
    fstat(fd, &st);
    off_t file_size = st.st_size;
    if (file_size == 0) {
        return 0;
    }

    void* fpointer = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    struct Item* curr_pointer = (struct Item*)fpointer;
    while (1) {
        printf("%d \n", curr_pointer->value);
        if (curr_pointer->next_pointer == 0) {
            break;
        }
        curr_pointer = (struct Item*)(fpointer + curr_pointer->next_pointer);
    }
    close(fd);
    return 0;
}