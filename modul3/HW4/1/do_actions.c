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
    buffer[pos++] = '\n';
    write(STDOUT_FILENO, buffer, pos);
}

void sigusr_handler(int signum)
{
    if (signum == SIGUSR1) {
        ++number;
    } else if (signum == SIGUSR2) {
        number *= -1;
    }
    print_int(number);
}

void sigterm_handler(int signum)
{
    _exit(0);
}

int main()
{
    struct sigaction sigusr_act;
    sigusr_act.sa_handler = sigusr_handler;

    sigaction(SIGUSR1, &sigusr_act, NULL);
    sigaction(SIGUSR2, &sigusr_act, NULL);

    struct sigaction sigterm_act;
    sigterm_act.sa_handler = sigterm_handler;
    sigterm_act.sa_flags |= SA_RESTART;

    sigaction(SIGTERM, &sigterm_act, NULL);
    sigaction(SIGINT, &sigterm_act, NULL);

    scanf("%d", &number);
    print_int(getpid());

    while (1) {
        pause();
    }

    return 0;
}