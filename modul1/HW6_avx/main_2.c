#include <stdio.h>
#include <stdlib.h>

extern float dot_product(size_t N, const float *A, const float *B);

int main() {
    int n = 15;
    float* a = malloc(n * sizeof(float));
    float* b = malloc(n * sizeof(float));
    
    for (int i = 0; i < n; ++i) {
        a[i] = i;
        b[i] = 0.125;
    }

    printf("%f\n", dot_product(n, a, b));

    free(a);
    free(b);
}