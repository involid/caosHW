#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signum, siginfo_t* info, void* ucontext)
{
    sigval_t value = info->si_value;
    if (value.sival_int == 0) {
        exit(0);
    }
    pid_t pid = info->si_pid;
    --value.sival_int;

    sigqueue(pid, SIGRTMIN, value);
}

int main()
{
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGRTMIN);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    struct sigaction act;
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;

    sigaction(SIGRTMIN, &act, NULL);

    while (1) {
        pause();
    }
    return 0;
}