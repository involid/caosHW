#include <limits.h>
#include <stdint.h>

extern void sum(ITYPE first, ITYPE second, ITYPE* res, int* CF)
{
    unsigned int length = sizeof(ITYPE) * CHAR_BIT;
    unsigned int carry = 0;
    ITYPE result = 0;
    for (unsigned int i = 0; i < length; ++i) {
        ITYPE digit = ((ITYPE)1 & (first ^ second ^ carry));
        result ^= (digit << i);
        if (carry) {
            carry = (first | second) & 1;
        } else {
            carry = first & second & 1;
        }

        second >>= 1;
        first >>= 1;
    }

    *CF = carry;
    *res = result;
}