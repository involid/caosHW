#include <iostream>
#include <string>

int main() {
    std::string s;
    getline(std::cin, s, {});
    std::cout << "Hello from program A\n";
    std::cout << s;
    std::cout << "Goodbye from program A\n";
    return 0;
}
