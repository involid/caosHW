#include <stdio.h>
#include <stdlib.h>

extern void sum(size_t N, const int *A, const int *B, int *R);
int sz = 1000;

int main() {
    int* A = malloc(sizeof(int) * 100);
    int* B = malloc(sizeof(int) * 100);
    int* R = malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; ++i) {
        A[i] = i + 1;
        B[i] = i + 1;
    }
    sum(100, A, B, R);
    for (int i = 0; i < 20; ++i) {
        printf("%d\n", R[i]);
    }
}