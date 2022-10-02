#include <stdio.h>

int main() {
    int a = 5;
    int* b = &a;
    *b = 6;
    printf("%i\n", a);
}