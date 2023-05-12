#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main () {
    //printf("%d\n", access("a.txt", F_OK));
    struct stat st;
    stat("a.txt", &st);
    FILE* x = fopen("x.txt", "w");
    fprintf(x, "%ld \n", st.st_size);
    fclose(x);
    printf("%ld \n", st.st_size);
}