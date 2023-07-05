#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

const __ssize_t magic_bytes_cnt = 4;
const char magic_bytes[4] = {0x7f, 0x45, 0x4c, 0x46};

bool check_elf(char *buff) {
  for (int i = 0; i < magic_bytes_cnt; ++i) {
    if (magic_bytes[i] != buff[i])
      return false;
  }
  return true;
}

int main() {
  struct stat st;
  char end_line[1];
  while (1) {
    char filepath[PATH_MAX];
    memset(filepath, 0, PATH_MAX);
    int res = scanf("%[^\n]", filepath);
    if (res == EOF)
      break;
    scanf("%c", end_line);
    lstat(filepath, &st);

    if (st.st_mode & S_IXUSR) {
      char buff[PATH_MAX];
      memset(buff, 0, PATH_MAX);
      int fd = open(filepath, O_RDONLY);

      int readed = read(fd, buff, magic_bytes_cnt);
      if (readed >= magic_bytes_cnt && check_elf(buff)) {
        close(fd);
        continue;
      }

      lseek(fd, 0, SEEK_SET);
      readed = read(fd, buff, 2);
      if (readed != 2 || buff[0] != '#' || buff[1] != '!') {
        close(fd);
        printf(filepath, '\n');
        continue;
      }
      readed = read(fd, buff, PATH_MAX);
      close(fd);

      char interpretator[PATH_MAX];
      memset(interpretator, 0, PATH_MAX);

      for (int i = 0; i < PATH_MAX; ++i) {
        if (buff[i] == '\n')
          break;
        interpretator[i] = buff[i];
      }
      res = lstat(interpretator, &st);
      if (res != 0 || (st.st_mode & S_IXUSR) == 0) {
        printf(filepath, '\n');
      }
    }
  }
}