#include <fcntl.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

const ssize_t buff_sz = 4096;
const ssize_t buff_int_sz = buff_sz / sizeof(int32_t);

void my_sort(int32_t* arr, int sz)
{
    for (int i = 0; i < sz; ++i) {
        for (int j = i + 1; j < sz; ++j) {
            if (arr[i] > arr[j]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

void copy(int src_fd, int dest_fd, int from, int to)
{
    lseek(src_fd, from, SEEK_SET);
    lseek(dest_fd, from, SEEK_SET);
    char buff[buff_sz];
    while (from < to) {
        int readed = read(src_fd, buff, buff_sz);
        write(dest_fd, buff, readed);
        from += readed;
    }
}

void merge(int from, int to, int fd, int helper_fd)
{
    int mid = (from + to) / 2;
    int buff1[buff_int_sz];
    int buff2[buff_int_sz];
    int buff_merged[buff_int_sz];
    int ptr1 = from;
    int ptr2 = mid;
    int buff1_ptr = buff_int_sz;
    int buff2_ptr = buff_int_sz;
    int buff_merged_ptr = 0;
    lseek(helper_fd, from * sizeof(int32_t), SEEK_SET);

    while (ptr1 < mid || ptr2 < to) {
        if (buff1_ptr == buff_int_sz) {
            lseek(fd, ptr1 * sizeof(int32_t), SEEK_SET);
            read(fd, (char*)buff1, buff_sz);
            buff1_ptr = 0;
        }
        if (buff2_ptr == buff_int_sz) {
            lseek(fd, ptr2 * sizeof(int32_t), SEEK_SET);
            read(fd, (char*)buff2, buff_sz);
            buff2_ptr = 0;
        }

        if (ptr2 == to ||
            (ptr1 != mid && buff1[buff1_ptr] < buff2[buff2_ptr])) {
            buff_merged[buff_merged_ptr] = buff1[buff1_ptr];
            ++buff_merged_ptr;
            ++buff1_ptr;
            ++ptr1;
        } else {
            buff_merged[buff_merged_ptr] = buff2[buff2_ptr];
            ++buff_merged_ptr;
            ++buff2_ptr;
            ++ptr2;
        }

        if (buff_merged_ptr == buff_int_sz) {
            write(helper_fd, (char*)buff_merged, buff_sz);
            buff_merged_ptr = 0;
        }
    }
    write(helper_fd, (char*)buff_merged, buff_merged_ptr * sizeof(int32_t));
    copy(helper_fd, fd, from * sizeof(int32_t), to * sizeof(int32_t));
}

void merge_sort(int fd, int helper_fd, int from, int to)
{
    if ((to - from) * sizeof(int32_t) <= buff_sz) {
        char buff[buff_sz];
        lseek(fd, from * sizeof(int32_t), SEEK_SET);
        read(fd, buff, (to - from) * sizeof(int32_t));
        my_sort((int32_t*)buff, (to - from));

        lseek(fd, from * sizeof(int32_t), SEEK_SET);
        lseek(helper_fd, from * sizeof(int32_t), SEEK_SET);
        write(fd, buff, (to - from) * sizeof(int32_t));
        write(helper_fd, buff, (to - from) * sizeof(int32_t));
        return;
    }

    int mid = (to + from) / 2;
    merge_sort(fd, helper_fd, from, mid);
    merge_sort(fd, helper_fd, mid, to);
    merge(from, to, fd, helper_fd);
}

int main(int argc, char* argv[])
{
    int fd = open(argv[1], O_RDWR);
    struct stat st;
    fstat(fd, &st);
    int helper_fd = open("sort_helper", O_RDWR | O_CREAT, 0644);
    copy(fd, helper_fd, 0, st.st_size);
    merge_sort(fd, helper_fd, 0, st.st_size / sizeof(int32_t));
    close(fd);
    close(helper_fd);
    return 0;
}