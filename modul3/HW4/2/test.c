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

        execl("signalfd_rtsig", "signalfd_rtsig", "A.txt", "B.txt", "C.txt", NULL);
        perror("exec");

    } else if (child_pid > 0) {
        // ===== Parent process =====
        
        sleep(1);
        sigval_t send_value;
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+1, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+3, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+3, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+1, send_value);
        sleep(1);
        kill(child_pid, SIGRTMIN+2);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+1, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+3, send_value);
        sleep(1);
        
        sigqueue(child_pid, SIGRTMIN+5, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+4, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+5, send_value);
        sleep(1);
        kill(child_pid, SIGRTMIN+5);
        sleep(1);
        kill(child_pid, SIGRTMIN+4);
        
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+2, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+3, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+3, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+3, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+3, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+1, send_value);
        sleep(1);
        sigqueue(child_pid, SIGRTMIN+0, send_value);
        sleep(1);

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
