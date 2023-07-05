#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int n;
  sscanf(argv[1], "%d", &n);
  int count = 1;

  while (1) {
    if (count == n) {
      printf("%d\n", n);
      fflush(stdout);
      break;
    } else {
      printf("%d ", count);
      fflush(stdout);
    }

    pid_t pid = fork();
    if (pid == 0) {
      ++count;
    } else {
      int wstatus = 0;
      waitpid(pid, &wstatus, 0);
      break;
    }
  }
}