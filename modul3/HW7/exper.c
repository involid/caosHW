#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>

void make_upper(char* arr, size_t size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] >= 'a' && arr[i] <= 'z') {
            arr[i] += 'A' - 'a';
        }
    }
}

int main() {
    char a[100] = "es Qez siryM EM 8888 gg";
    make_upper(a, sizeof("es Qez siryM EM 8888 gg"));
    printf("%s", a);
}