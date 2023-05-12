#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int pipefd[2];
    int pipe_result = pipe(pipefd);
    if (pipe_result != 0) perror("pipe");

    pid_t child_pid = fork();
    if (child_pid == 0) {
        // ===== Child process =====

        int dup2_result = dup2(pipefd[1], STDOUT_FILENO);
        if (dup2_result == -1) perror("dup2");

        int close_result = close(pipefd[0]);
        if (close_result == -1) perror("close");
        close_result = close(pipefd[1]);
        if (close_result == -1) perror("close");

        execl(argv[1], argv[1], NULL);
        perror("exec");

    } else if (child_pid > 0) {
        // ===== Parent process =====

        int dup2_result = dup2(pipefd[0], STDIN_FILENO);
        if (dup2_result == -1) perror("dup2");

        int close_result = close(pipefd[0]);
        if (close_result == -1) perror("close");
        close_result = close(pipefd[1]);
        if (close_result == -1) perror("close");

        pid_t child_pid_read;
        scanf("%d", &child_pid_read);
        printf("child_pid %d\n", child_pid);
        printf("child_pid_read %d\n", child_pid_read);

        sleep(1);
        kill(child_pid_read, SIGUSR1);
        sleep(1);
        kill(child_pid_read, SIGUSR1);
        sleep(1);
        kill(child_pid_read, SIGUSR1);
        sleep(1);
        kill(child_pid_read, SIGUSR2);
        sleep(1);
        kill(child_pid_read, SIGUSR1);
        sleep(1);
        kill(child_pid_read, SIGUSR2);
        sleep(1);
        kill(child_pid_read, SIGUSR1);
        sleep(1);
        kill(child_pid_read, SIGUSR1);
        sleep(1);
        kill(child_pid_read, SIGUSR1);
        sleep(1);
        // kill(child_pid_read, SIGTERM);
        kill(child_pid_read, SIGINT);
        sleep(1);

        int value;
        while (scanf("%d", &value) > 0) {
            printf("%d\n", value);
        }

        int status = 0;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status)) {
            // Child process was terminated via exit
            printf("EXIT with return code %d\n", WEXITSTATUS(status));
        }
        if (WIFSIGNALED(status)) {
            // Child process was terminated via signal
            printf("SIGNAL with signal %d\n", WTERMSIG(status));
        }

    } else {
        perror("fork");
    }

    return 0;
}
