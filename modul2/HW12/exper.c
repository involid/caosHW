#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

const size_t MAX_SIZE = 4096;

int main() {
    FILE * fp = fopen("aaaaa", "w");
    fprintf(fp, "%%s");
    //remove("main.c");
}