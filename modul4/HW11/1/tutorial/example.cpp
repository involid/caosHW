#include "example.hpp"

#include <iostream>

ExampleClass::ExampleClass() {
  std::cout << "ExampleClass Constructor\n";
}

ExampleClass::~ExampleClass() {
  std::cout << "ExampleClass Destructor\n";
}

int ExampleClass::Print(int, bool) {
  std::cout << "ExampleClass Print\n";
  return 0;
}
