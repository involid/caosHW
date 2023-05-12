#include <iostream>
#include <string>

int main() {
    std::string s;
    getline(std::cin, s, {});
    std::cout << "Hello from program B\n";
    std::cout << s;
    std::cout << "Goodbye from program B\n";
    return 0;
}
