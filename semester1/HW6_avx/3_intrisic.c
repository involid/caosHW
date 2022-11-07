#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

void sub(int size, double** matrix, int dest, int src)
{
    double div = matrix[dest][src] / matrix[src][src];
    __m256d _div = {div, div, div, div};
    for (int i = 0; i + 3 <= size; i += 4) {
        __m256d _sub = _mm256_mul_pd(_mm256_load_pd(matrix[src] + i), _div);
        __m256d _res = _mm256_sub_pd(_mm256_load_pd(matrix[dest] + i), _sub);
        _mm256_store_pd(matrix[dest] + i, _res);
    }
}

void gauss_elemination(int size, double** matrix)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                continue;
            }
            //matrix[j] -= matrix[j][i] / matrix[i][i] * matrix[i]
            sub(size, matrix, j, i);
        }
    }
}

void print_ans(int size, double** matrix)
{
    for (int i = 0; i < size; ++i) {
        printf("%lf\n", matrix[i][size] / matrix[i][i]);
    }
}

int main()
{
    int size;
    scanf("%d", &size);
    double** matrix = malloc(size * sizeof(double*));
    for (int i = 0; i < size; ++i) {
        matrix[i] = aligned_alloc(32, (size + 1) * sizeof(double));
        for (int j = 0; j <= size; ++j) {
            scanf("%lf", matrix[i] + j);
        }
    }

    gauss_elemination(size, matrix);
    print_ans(size, matrix);

    for (int i = 0; i < size; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}