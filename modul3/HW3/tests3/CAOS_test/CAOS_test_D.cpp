#include <iostream>
#include <string>

int main() {
    std::string s;
    getline(std::cin, s, {});
    std::cout << "Hello from program D\n";
    std::cout << s;
    std::cout << "Goodbye from program D\n";
    return 0;
}
