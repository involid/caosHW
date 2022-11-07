#include <stdio.h>
#include <stdlib.h>

extern void mergesort(int from, int to, const int *in, int *out);


int main() {
    int* A = malloc(sizeof(int) * 100);
    int* B = malloc(sizeof(int) * 100);
    for (int i = 0; i < 6; ++i) {
        A[i] = i + 4;
    }
    for (int i = 6; i < 10; ++i) {
        A[i] = i - 7;
    }
    for (int i = 10; i < 14; ++i) {
        A[i] = i - 12;
    }
    A[6] = -233;
    A[7] = 124124;
    A[10] = 1000;

    mergesort(4, 12, A, B);

    for (int i = 0; i < 14; ++i) {
        printf("%d %d %d\n", i, A[i], B[i]);
    }
}