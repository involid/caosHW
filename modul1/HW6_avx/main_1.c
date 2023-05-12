#include <stdio.h>

extern double avx_sin(double x);

int main() {
    printf("%f\n", avx_sin(1.0)); //0.841471
    return 0;
}
 