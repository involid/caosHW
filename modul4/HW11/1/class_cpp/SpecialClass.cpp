#include "../class_hpp/SpecialClass.hpp"

#include <iostream>

SpecialClass::SpecialClass() {
  std::cout << "Special Class constructor called" << std::endl;
}

SpecialClass::~SpecialClass() {
  std::cout << "Special Class destructor called" << std::endl;
}

void SpecialClass::Print(int value) {
  std::cout << "Special Class Print with value " << value << std::endl;
}
