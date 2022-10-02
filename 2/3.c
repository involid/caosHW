#include <stdint.h>
#include <stdio.h>

int char_code(char symbol)
{
    if ('0' <= symbol && symbol <= '9') {
        return (symbol - '0');
    }
    if ('A' <= symbol && symbol <= 'Z') {
        return (symbol - 'A') + 10;
    }
    return (symbol - 'a') + 36;
}

void print_ans(uint64_t set)
{
    for (int i = 0; i < 62; ++i) {
        if (set & 1) {
            if (i < 10) {
                printf("%i", i);
            }
            if (i >= 10 && i < 36) {
                printf("%c", 'A' + i - 10);
            }
            if (i >= 36 && i < 62) {
                printf("%c", 'a' + i - 36);
            }
        }
        set >>= 1;
    }
}

uint64_t do_op(char op, uint64_t mask1, uint64_t mask2)
{
    if (op == '|') {
        return mask1 | mask2;
    }
    if (op == '&') {
        return mask1 & mask2;
    }
    if (op == '^') {
        return mask1 ^ mask2;
    }
    //if (op == '~')
    return ~mask1;
}

int main()
{
    uint64_t set = 0;
    uint64_t mask = 0;
    char element;
    while (1) {
        element = getchar();
        if (element == EOF)
            break;
        if (element == '&' || element == '|' || element == '^' ||
            element == '~') {
            set = do_op(element, set, mask);
            mask = 0;
            continue;
        }
        mask |= ((uint64_t)1 << char_code(element));
    }
    print_ans(set);
    return 0;
}