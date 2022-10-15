#include <stdint.h>
#include <stdio.h>

typedef enum {
    PlusZero = 0x00,
    MinusZero = 0x01,
    PlusInf = 0xF0,
    MinusInf = 0xF1,
    PlusRegular = 0x10,
    MinusRegular = 0x11,
    PlusDenormal = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN = 0x30,
    QuietNaN = 0x31
} float_class_t;

extern float_class_t classify(double* value_ptr)
{
    void* void_value_ptr = value_ptr;
    uint64_t* uint_value_ptr = void_value_ptr;
    uint64_t value = *uint_value_ptr;
    uint64_t max_bit = ((uint64_t)1 << 63);
    int exp_sz = 11;
    int mantissa_sz = 52;

    int sign = (max_bit & value) ? 1 : 0;

    int exp_has_zero = 0;
    int exp_has_one = 0;
    for (int i = 1; i <= exp_sz; ++i) {
        if (value & (max_bit >> i)) {
            exp_has_one = 1;
        } else {
            exp_has_zero = 1;
        }
    }

    uint64_t mantissa_max_bit = (value & (max_bit >> (exp_sz + 1)));
    int mantissa_has_one = 0;
    for (int i = 1 + exp_sz; i < 1 + exp_sz + mantissa_sz; ++i) {
        if (value & (max_bit >> i)) {
            mantissa_has_one = 1;
        }
    }

    if (!exp_has_one) {
        if (!mantissa_has_one) {
            return (sign ? MinusZero : PlusZero);
        }

        if (sign) {
            return MinusDenormal;
        }
        return PlusDenormal;
    }

    if (!exp_has_zero) {
        if (!mantissa_has_one) {
            return (sign ? MinusInf : PlusInf);
        }

        if (mantissa_max_bit) {
            return QuietNaN;
        }
        return SignalingNaN;
    }

    if (sign) {
        return MinusRegular;
    }
    return PlusRegular;
}

int main() {
    double a = 1.0 / 0 + -1.0/0;
    //printf("%lu\n", max_bit + exp_bits + mantissa_bits + 1);
    printf("%d\n", classify(&a));
}