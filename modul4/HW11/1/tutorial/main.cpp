#include "example.hpp"

#include <iostream>

int main() {
  std::cout << sizeof(ExampleClass) << '\n';

  ExampleClass example;
  example.Print(0, true);
  return 0;
}
