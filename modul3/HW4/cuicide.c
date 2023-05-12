#include <signal.h>
#include <sys/types.h>

int main() {
    kill(-1, SIGKILL);
    return 0;
}