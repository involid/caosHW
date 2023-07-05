#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

void print_number(int num) {
  const int max_digits = 12;
  char buff[max_digits];
  int pos = 0;
  if (num < 0) {
    num = -num;
    buff[0] = '-';
    ++pos;
  }
  int deg = 1;
  while (deg <= num) {
    deg *= 10;
  }
  deg /= 10;
  if (deg == 0) {
    buff[pos++] = 0;
  }
  while (deg) {
    buff[pos] = num / deg + '0';
    num -= (num / deg) * deg;
    ++pos;
    deg /= 10;
  }
  buff[pos++] = '\n';
  write(1, buff, pos);
}

struct Item {
  int value;
  uint32_t next_pointer;
};

const ssize_t item_sz = sizeof(struct Item);

int main(int argc, char *argv[]) {
  int fd = open(argv[1], O_RDONLY);
  char buff[item_sz];
  int readed = read(fd, buff, item_sz);
  if (readed < item_sz)
    return 0;

  struct Item *curr = (struct Item *)buff;
  ssize_t curr_pos = 0;
  while (1) {
    print_number(curr->value);
    if ((curr->next_pointer) == 0) {
      break;
    }

    lseek(fd, curr->next_pointer, SEEK_SET);
    readed = read(fd, buff, item_sz);
    curr = (struct Item *)buff;
  }
  close(fd);
  return 0;
}