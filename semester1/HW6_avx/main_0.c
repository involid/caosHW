#include <stdio.h>
#include <stdlib.h>

extern double very_important_function(size_t N, const float *A, const float *B, float *R);

int main() {
    float* a = aligned_alloc(32, 16 * sizeof(float));
    float* b = aligned_alloc(32, 16 * sizeof(float));
    float* c = aligned_alloc(32, 16 * sizeof(float));
    for (int i = 0; i < 16; ++i) {
        a[i] = i;
        b[i] = 0.5;
    }
    
    printf("%f\n", very_important_function(16, a, b, c));
    
    for (int i = 0; i < 16; ++i) {
        printf("%f ", c[i]);
    }
    free(a);
    free(b);
    free(c); 
}