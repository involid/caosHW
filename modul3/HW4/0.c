#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static sig_atomic_t ans = 0;
static sig_atomic_t dont_terminate = 1;

void handler(int signum)
{
    if (signum == SIGTERM) {
        dont_terminate = 0;
    } else if (signum == SIGINT) {
        ++ans;
    }
}

int main()
{
    struct sigaction act;
    act.sa_handler = handler;

    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);

    printf("%i\n", getpid());
    fflush(stdout);
    while (dont_terminate) {
        pause();
    }

    printf("%i\n", ans);
    return 0;
}
