#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int value = 404;

void handler(int signum, siginfo_t* info, void* ucontext) {
    if (signum == SIGRTMIN) {
        value = info->si_value.sival_int;
        // I'm not sure that this is signal safety
        // But it is only test
    }
}

int main(int argc, char* argv[]) {
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // ===== Child process =====

        execl(argv[1], argv[1], NULL);
        perror("exec");

    } else if (child_pid > 0) {
        // ===== Parent process =====

        struct sigaction act_work;
        act_work.sa_sigaction = handler;
        sigemptyset(&act_work.sa_mask);
        act_work.sa_flags = SA_SIGINFO;

        sigaction(SIGRTMIN, &act_work, NULL);


        sigval_t send_value;

        sleep(1);
        kill(child_pid, SIGINT);
        sleep(1);
        sigqueue(child_pid, SIGINT, send_value);
        sleep(1);

        for (int i = 7; i >= 0; --i) {
            value = 404;
            
            sleep(1);
            sigqueue(child_pid, SIGRTMIN+i+1, send_value);
            sleep(1);
            
            value = 404;
            
            sleep(1);
            send_value.sival_int = i;
            sigqueue(child_pid, SIGRTMIN, send_value);
            sleep(1);
            printf("%d\n", value);
            sleep(1);
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
