#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

static const int BUFFER_SIZE = 4096;
const int no_file_error = 2;

ssize_t dump_char_buffer(int fd, char buffer[], int buffer_size)
{
    return write(fd, buffer, buffer_size);
}

int main(int argc, char* argv[])
{
    char input_buffer[BUFFER_SIZE];
    char digit_buffer[BUFFER_SIZE];
    char other_buffer[BUFFER_SIZE];

    int exit_code = 0;

    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        if (errno == no_file_error) {
            return 1;
        }
        return 3;
    }

    int digit_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
    int other_fd = open(argv[3], O_WRONLY | O_CREAT, 0644);

    if (digit_fd == -1 || other_fd == -1) {
        return 2;
    }

    ssize_t read_count = 0;
    ssize_t digit_count = 0;
    ssize_t other_count = 0;
    while (1) {
        read_count = read(input_fd, input_buffer, BUFFER_SIZE);
        if (read_count < 0) {
            return 2;
        }
        if (read_count == 0) {
            break;
        }

        for (int i = 0; i < read_count; ++i) {
            if ('0' <= input_buffer[i] && input_buffer[i] <= '9') {
                digit_buffer[digit_count++] = input_buffer[i];
                if (digit_count == BUFFER_SIZE) {
                    ssize_t res =
                        dump_char_buffer(digit_fd, digit_buffer, digit_count);
                    if (res < 0)
                        return 2;
                    digit_count = 0;
                }
            } else {
                other_buffer[other_count++] = input_buffer[i];
                if (other_count == BUFFER_SIZE) {
                    ssize_t res =
                        dump_char_buffer(other_fd, other_buffer, other_count);
                    if (res < 0)
                        return 2;
                    other_count = 0;
                }
            }
        }
    }
    if (digit_count > 0) {
        ssize_t res = dump_char_buffer(digit_fd, digit_buffer, digit_count);
        if (res < 0)
            return 2;
    }
    if (other_count > 0) {
        ssize_t res = dump_char_buffer(other_fd, other_buffer, other_count);
        if (res < 0)
            return 2;
    }

    close(input_fd);
    close(digit_fd);
    close(other_fd);

    return exit_code;
}