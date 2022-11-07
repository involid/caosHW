#include <stdint.h>
#include <stdio.h>

void print_ans(int val1, int val2)
{
    printf("%i", val1);
    printf(" %i\n", val2);
}

int main()
{
    int cnt_ascii = 0;
    int cnt_utf8 = 0;

    uint8_t max_bit = 1 << 7;
    uint8_t max2_bits = max_bit ^ (max_bit >> 1);

    char symbol;
    while (1) {
        int x = getchar();
        if (x == EOF) {
            break;
        }
        symbol = x;
        void* void_ptr = &symbol;
        uint8_t* ptr = void_ptr;
        uint8_t val = *ptr;

        int byte_count = 0;
        for (int i = 0; i < 8; ++i) {
            if (val & max_bit) {
                ++byte_count;
                val <<= 1;
                continue;
            }
            break;
        }
        if (byte_count == 0) {
            ++cnt_ascii;
            continue;
        }

        if (byte_count == 1 || byte_count > 4) {
            print_ans(cnt_ascii, cnt_utf8);
            return 1;
        }

        for (int i = 1; i < byte_count; ++i) {
            scanf("%c", &symbol);
            void_ptr = &symbol;
            ptr = void_ptr;
            val = *ptr;
            if ((val & max2_bits) != max_bit) {
                print_ans(cnt_ascii, cnt_utf8);
                return 1;
            }
        }
        ++cnt_utf8;
    }
    print_ans(cnt_ascii, cnt_utf8);
    return 0;
}