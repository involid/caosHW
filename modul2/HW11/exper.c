#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int count = 1;

int main() {
    pid_t root_pid = getpid();
    char buff[100];

    pid_t pid = fork();

    if (pid == 0) {
        exit(3);
    }
    else {
        int wstatus;
        waitpid(pid, &wstatus, 0);
        printf("%d", wstatus);
    }
    return 1;
}