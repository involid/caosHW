#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const off_t BUFF_SIZE = 4096;

int main() {
  int count = 0;
  char buff[BUFF_SIZE];
  pid_t parent_pid = getpid();

  while (1) {
    if (getpid() != parent_pid) {
      if (scanf("%s", buff) == EOF) {
        exit(count);
      } else {
        ++count;
      }
    }

    pid_t pid = fork();
    if (pid > 0) {
      int wstatus;
      waitpid(pid, &wstatus, 0);
      count = WEXITSTATUS(wstatus);
      break;
    }
  }
  if (getpid() == parent_pid) {
    printf("%d\n", count);
    return 0;
  }
  return count;
}