#include <stdio.h>

int sum(int x0, size_t N, int *X);

int main() {
    int X[10];
    for (int i = 0; i < 5; ++i) {
        X[i] = i + 1; 
    }
    printf("%d\n", sum(0, 5, X));
}