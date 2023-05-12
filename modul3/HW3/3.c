#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void close_pipes(int** pipes, int size)
{
    for (int i = 0; i < size; ++i) {
        if (close(pipes[i][0]) == -1) {
            perror("close");
        }
        if (close(pipes[i][1]) == -1) {
            perror("close");
        }
    }
}

int main(int argc, char* argv[])
{
    --argc;
    int** pipefd = calloc(sizeof(int*), argc - 1);
    if (pipefd == NULL) {
        perror("calloc");
    }
    for (int i = 0; i < argc - 1; ++i) {
        pipefd[i] = calloc(sizeof(int), 2);
        if (pipefd[i] == NULL) {
            perror("calloc");
        }
    }

    for (int i = 0; i < argc - 1; ++i) {
        if (pipe(pipefd[i]) == -1) {
            perror("pipe");
        }
    }

    pid_t* childs = calloc(sizeof(pid_t), argc);
    if (childs == NULL) {
        perror("calloc");
    }
    // first child
    childs[0] = fork();
    if (childs[0] == -1) {
        perror("fork");
    }
    if (childs[0] == 0) {
        if (dup2(pipefd[0][1], STDOUT_FILENO) == -1) {
            perror("dup2");
        }
        close_pipes(pipefd, argc - 1);
        if (execlp(argv[1], argv[1], NULL) == -1) {
            perror("exec");
        }
    }

    // n - 2 childs
    for (int i = 1; i < argc - 1; ++i) {
        childs[i] = fork();
        if (childs[i] == -1) {
            perror("fork");
        }
        if (childs[i] == 0) {
            if (dup2(pipefd[i - 1][0], STDIN_FILENO) == -1) {
                perror("dup2");
            }
            if (dup2(pipefd[i][1], STDOUT_FILENO) == -1) {
                perror("dup2");
            }
            close_pipes(pipefd, argc - 1);
            if (execlp(argv[i + 1], argv[i + 1], NULL) == -1) {
                perror("exec");
            }
        }
    }

    // last child
    childs[argc - 1] = fork();
    if (childs[argc - 1] == -1) {
        perror("fork");
    }
    if (childs[argc - 1] == 0) {
        if (dup2(pipefd[argc - 2][0], STDIN_FILENO) == -1) {
            perror("dup2");
        }
        close_pipes(pipefd, argc - 1);
        if (execlp(argv[argc], argv[argc], NULL) == -1) {
            perror("exec");
        }
    }

    close_pipes(pipefd, argc - 1);
    int wstatus = 0;
    for (int i = 0; i < argc; ++i) {
        if (waitpid(childs[i], &wstatus, 0) == -1) {
            perror("waitpid");
        }
    }
    free(pipefd);
    return 0;
}