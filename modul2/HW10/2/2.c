#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const int BUFF_SIZE = 32;

void write_number(int number, char* pointer, int width) {
    char buff[BUFF_SIZE];
    sprintf(buff, "%d", number);
    int curr = width;
    int buff_curr = 0;
    while (buff[buff_curr]) {
        ++buff_curr;
    }
    for (int i = 0; i < width - buff_curr; ++i) {
        pointer[i] = ' ';
    }
    for (int i = width - buff_curr; i < width; ++i) {
        pointer[i] = buff[i - width + buff_curr];
    }
}

enum direction {
    left,
    up,
    right,
    down
};

void write_spiral(char* fpointer, int n, int width) {
    /*
    fpointer[0] = '1';
    fpointer[1] = ' ';
    fpointer[2] = '2';
    fpointer[3] = '\n';
    fpointer[4] = '4';
    fpointer[5] = ' ';
    fpointer[6] = '3';
    fpointer[7] = '\n';
    */
    int** matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        matrix[i] = malloc(n * sizeof(int));
    }
    int pos_x = 0;
    int pos_y = 0;
    int left_bound = -1;
    int up_bound = -1;
    int right_bound = n;
    int down_bound = n;
    enum direction direction = right;
    for (int i = 1; i <= n * n; ++i) {
        matrix[pos_x][pos_y] = i;
        if (direction == right) {
            if (pos_x + 1 == right_bound) {
                ++up_bound;
                direction = down;
                ++pos_y;
            }
            else {
                ++pos_x;
            }
        }
        else if (direction == down) {
            if (pos_y + 1 == down_bound) {
                --right_bound;
                direction = left;
                --pos_x;
            }
            else {
                ++pos_y;
            }
        }
        else if (direction == left) {
            if (pos_x - 1 == left_bound) {
                --down_bound;
                direction = up;
                --pos_y;
            }
            else {
                --pos_x;
            }
        }
        else if (direction == up) {
            if (pos_y - 1 == up_bound) {
                ++left_bound;
                direction = right;
                ++pos_x;
            }
            else {
                --pos_y;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            write_number(matrix[j][i], fpointer, width);
            fpointer += width;
        }
        *fpointer = '\n';
        ++fpointer;
    }
    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char* argv[]) {
    int n;
    sscanf(argv[2], "%d", &n);
    int width;
    sscanf(argv[3], "%d", &width);
    off_t fsize = n * (n * width + 1);
    int fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    lseek(fd, fsize - 1, SEEK_SET);
    
    write(fd, "\0", 1);
    char* fpointer = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    write_spiral(fpointer, n, width);

    munmap(fpointer, fsize);
    close(fd);
    return 0;
}