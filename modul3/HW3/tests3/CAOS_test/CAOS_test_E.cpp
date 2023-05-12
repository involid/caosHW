#include <iostream>
#include <string>

int main() {
    std::string s;
    getline(std::cin, s, {});
    std::cout << "Hello from program E\n";
    std::cout << s;
    std::cout << "Goodbye from program E\n";
    return 0;
}
