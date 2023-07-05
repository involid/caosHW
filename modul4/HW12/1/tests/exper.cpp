#include <iostream>

int factors_num(int number) {
    if (number < 0) {
        number = -number;
    }
    std::cout << number << '\n';
    int num = 0;
    int prime = 2;
    while (number > 1) {
        if (number % prime == 0) {
            number /= prime;
            ++num;
            std::cout << num << '\n';
        }
        else {
            ++prime;
        }
    }
    return num;
}

int main() {
    std::cout << factors_num(6);
}