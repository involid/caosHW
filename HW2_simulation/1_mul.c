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

extern void mul(ITYPE first, ITYPE second, ITYPE* res, int* CF)
{
    unsigned int length = sizeof(ITYPE) * CHAR_BIT;
    *res = 0;
    ITYPE check_cf = 0;
    ITYPE max_bit = (ITYPE)1 << (length - 1);
    for (unsigned int i = 0; i < length; ++i) {
        if (second & 1) {
            if (check_cf & first) {
                *CF = 1;
                return;
            }
            sum(*res, (first << i), res, CF);
            if (*CF) {
                return;
            }
        }

        check_cf >>= 1;
        check_cf ^= max_bit;
        second >>= 1;
    }
}
