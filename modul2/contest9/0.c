#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  uint64_t total_size = 0;

  struct stat st;
  char filepath[PATH_MAX];
  char end_line[1];
  while (scanf("%[^\n]", filepath) != EOF) {
    lstat(filepath, &st);

    if (S_ISREG(st.st_mode)) {
      off_t file_size = st.st_size;
      total_size += file_size;
    }
    scanf("%c", end_line);
  }

  printf("%llu", total_size);
}