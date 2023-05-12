#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_NUMBER_SIZE 20

volatile static sig_atomic_t number;

void print_int(int number)
{
    char buffer[MAX_NUMBER_SIZE];
    int pos = 0;
    bool is_negative = false;
    if (number < 0) {
        is_negative = true;
        number = -number;
    }
    if (number == 0) {
        buffer[pos++] = '0';
    }
    while (number != 0) {
        buffer[pos++] = '0' + (number % 10);
        number /= 10;
    }
    if (is_negative) {
        buffer[pos++] = '-';
    }
    for (int i = 0; i < pos / 2; ++i) {
        char tmp = buffer[i];
        buffer[i] = buffer[pos - i - 1];
        buffer[pos - i - 1] = tmp;
    }
    //buffer[pos] = '\n';
    write(STDOUT_FILENO, buffer, pos);
}



int main() {
    while (1) {
        int a;
        scanf("%d", &a);
        print_int(a);
        printf("\n");
    }
    //print_number(-50);
}