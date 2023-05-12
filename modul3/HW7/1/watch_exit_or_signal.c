#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // ===== Child process =====

        execl(argv[1], argv[1], argv[2], NULL);
        perror("exec");

    } else if (child_pid > 0) {
        // ===== Parent process =====

        FILE* pid_process = fopen("pid_process.txt", "w+");
        fprintf(pid_process, "%ld", (long int)child_pid);
        fflush(pid_process);
        fclose(pid_process);

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
