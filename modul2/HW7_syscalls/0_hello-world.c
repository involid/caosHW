#include <sys/syscall.h>

long syscall(long number, ...);

static const char MESSAGE[] = "Hello, World!\n";
static const int MESSAGE_SIZE = sizeof(MESSAGE) - 1;

void _start() {
    syscall(SYS_write, 1, MESSAGE, MESSAGE_SIZE);

    syscall(SYS_exit, 0);
}