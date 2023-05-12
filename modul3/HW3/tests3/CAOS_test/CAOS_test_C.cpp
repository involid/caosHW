#include <iostream>
#include <string>

int main() {
    std::string s;
    getline(std::cin, s, {});
    std::cout << "Hello from program C\n";
    std::cout << s;
    std::cout << "Goodbye from program C\n";
    return 0;
}
