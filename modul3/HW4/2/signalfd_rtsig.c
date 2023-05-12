#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 4096
#define MAX_FILES 4096

volatile int file_fds[MAX_FILES];
volatile size_t size;

void finish_program()
{
    for (int i = 0; i < size; ++i) {
        close(file_fds[i]);
    }
    _exit(0);
}

int read_line(int fd, char* buff)
{
    int num_read = 0;
    char next_char;

    while (num_read < BUFF_SIZE - 1) {
        int readed = read(fd, &next_char, 1);

        if (readed == -1) {
            return -1;
        } else if (readed == 0) {
            break;
        } else {
            ++num_read;
            *(buff++) = next_char;
            if (next_char == '\n') {
                break;
            }
        }
    }
    *buff = '\0';
    return num_read;
}

void handler(int signum)
{
    if (signum == SIGRTMIN) {
        finish_program();
    } else if (signum - SIGRTMIN <= size) {
        char buff[BUFF_SIZE];
        int readed = read_line(file_fds[signum - SIGRTMIN - 1], buff);
        if (readed == -1) {perror("read");}
        write(STDOUT_FILENO, buff, readed);
    }
}

int main(int argc, char** argv)
{
    size = argc - 1;
    for (int i = 0; i < size; ++i) {
        file_fds[i] = open(argv[i + 1], O_RDONLY);
    }

    sigset_t mask;
    sigfillset(&mask);
    for (int sig = SIGRTMIN; sig <= SIGRTMAX; ++sig) {
        sigdelset(&mask, sig);
    }
    sigprocmask(SIG_SETMASK, &mask, NULL);

    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags |= SA_RESTART;
    for (int sig = SIGRTMIN; sig <= SIGRTMAX; ++sig) {
        sigaction(sig, &act, NULL);
    }

    while (1) {
        pause();
    }

    return 0;
}