#include "../../../class_hpp/some/package/ClassInPackage.hpp"

#include <iostream>

namespace some::package {
 
ClassInPackage::ClassInPackage() {
  value = 10;
  std::cout << "ClassInPackage() : " << value << std::endl;
}

ClassInPackage::~ClassInPackage() {
  std::cout << "~ClassInPackage() : " << value << std::endl;  
}

void ClassInPackage::SetValue(int new_value) {
  value = new_value;
  std::cout << "SetValue() : " << value << std::endl;
}

int ClassInPackage::GetValue() {
  std::cout << "GetValue() : " << value << std::endl;
  return value;
}

}  // namespace some::package
