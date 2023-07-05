#include <stdint.h>
#include <windows.h>

void print_number(int num) {
  const int max_digits = 12;
  CHAR buff[max_digits];
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

  HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
  WriteFile(stdout_handle, buff, pos, NULL, NULL);
}

struct Item {
  int value;
  uint32_t next_pointer;
};

const ssize_t item_sz = sizeof(struct Item);

int main(int argc, CHAR *argv[]) {
  HANDLE handle = CreateFileA(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  CHAR buff[item_sz];
  DWORD readed;
  ReadFile(handle, buff, item_sz, &readed, NULL);
  if (readed < item_sz)
    return 0;

  struct Item *curr = (struct Item *)buff;
  ssize_t curr_pos = 0;
  while (1) {
    print_number(curr->value);
    if ((curr->next_pointer) == 0) {
      break;
    }

    SetFilePointer(handle, curr->next_pointer, NULL, FILE_BEGIN);

    ReadFile(handle, buff, item_sz, &readed, NULL);
    curr = (struct Item *)buff;
  }
  CloseHandle(handle);
  return 0;
}