#include <sys/syscall.h>

long syscall(long number, ...);

const int buff_size = 4096;

void _start() {
  char buff[buff_size];
  while (1) {
    int readed = syscall(SYS_read, 0, buff, buff_size);
    if (!readed) {
      break;
    }
    syscall(SYS_write, 1, buff, readed);
  }

  syscall(SYS_exit, 0);
}