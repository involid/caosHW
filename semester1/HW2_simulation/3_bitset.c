#include <stdint.h>
#include <stdio.h>

const int cap_letter_begining = 10;
const int low_letter_begining = 36;
const int alphabet_sz = 62;

int char_code(char symbol)
{
    if ('0' <= symbol && symbol <= '9') {
        return (symbol - '0');
    }
    if ('A' <= symbol && symbol <= 'Z') {
        return (symbol - 'A') + cap_letter_begining;
    }
    return (symbol - 'a') + low_letter_begining;
}

void print_ans(uint64_t set)
{
    for (int i = 0; i < alphabet_sz; ++i) {
        if (set & 1) {
            if (i < cap_letter_begining) {
                printf("%i", i);
            }
            if (i >= cap_letter_begining && i < low_letter_begining) {
                printf("%c", 'A' + i - cap_letter_begining);
            }
            if (i >= low_letter_begining && i < alphabet_sz) {
                printf("%c", 'a' + i - low_letter_begining);
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