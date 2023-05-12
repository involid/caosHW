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

const int exp_sz = 11;
const int mantissa_sz = 52;
const int bit_sz = 64;
const uint64_t exp_bits =
    ((((uint64_t)1 << exp_sz) - 1)
     << mantissa_sz); //0111111111110000000000000000000000000000000000000000000000000000
const uint64_t mantissa_bits =
    ((uint64_t)1 << mantissa_sz) -
    1; //0000000000001111111111111111111111111111111111111111111111111111
const uint64_t max_bit =
    ((uint64_t)1
     << (bit_sz -
         1)); //1000000000000000000000000000000000000000000000000000000000000000

extern float_class_t classify(double* value_ptr)
{
    void* void_value_ptr = value_ptr;
    uint64_t* uint_value_ptr = void_value_ptr;
    uint64_t value = *uint_value_ptr;

    int sign = (max_bit & value) ? 1 : 0;

    int exp_has_zero = (((exp_bits & value) == exp_bits) ? 0 : 1);
    int exp_has_one = (exp_bits & value ? 1 : 0);

    uint64_t mantissa_max_bit = (value & (max_bit >> (exp_sz + 1)));
    int mantissa_has_one = (mantissa_bits & value ? 1 : 0);

    float_class_t ans;

    if (!exp_has_one) {
        if (!mantissa_has_one) {
            ans = (sign ? MinusZero : PlusZero);
        } else {
            ans = (sign ? MinusDenormal : PlusDenormal);
        }
    } else if (!exp_has_zero) {
        if (!mantissa_has_one) {
            ans = (sign ? MinusInf : PlusInf);
        } else {
            ans = (mantissa_max_bit ? QuietNaN : SignalingNaN);
        }
    } else {
        ans = (sign ? MinusRegular : PlusRegular);
    }
    return ans;
}

int main() {
    double a = 1;
    double b = 0;
    a = a / b + a / b;
    printf("%d", classify(&a));
}