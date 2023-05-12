#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Creating pipes");
    }

    pid_t child1_pid = fork();
    if (child1_pid == -1) {
        perror("Forking first child");
    }
    if (child1_pid == 0) {
        if (close(pipefd[0]) == -1) {
            perror("close");
        }

        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("First child stdout");
        }
        if (close(pipefd[1]) == -1) {
            perror("close");
        }

        if (execlp(argv[1], argv[1], NULL) == -1) {
            perror("Exec of first child");
        }
    }

    pid_t child2_pid = fork();
    if (child2_pid == -1) {
        perror("Forking second child");
    }
    if (child2_pid == 0) {
        if (close(pipefd[1]) == -1) {
            perror("close");
        }

        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("Second child stdin");
        }
        if (close(pipefd[0]) == -1) {
            perror("close");
        }

        if (execlp(argv[2], argv[2], NULL) == -1) {
            perror("Exec of second child");
        }
    }

    if (close(pipefd[0]) == -1) {
        perror("close");
    }
    if (close(pipefd[1]) == -1) {
        perror("close");
    }

    int wstatus = 0;
    if (waitpid(child1_pid, &wstatus, 0) == -1) {
        perror("waitpid");
    }
    if (waitpid(child2_pid, &wstatus, 0) == -1) {
        perror("waitpid");
    }
    return 0;
}