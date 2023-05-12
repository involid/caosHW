// g++ tutorial.cpp -ldl -o tutorial

#include <dlfcn.h>
#include <stdio.h>
#include "example.hpp"

int main() {
  void* library = dlopen("./libexample.so", RTLD_LAZY);
  if (library == NULL) {
    fprintf(stderr, "dlopen error: %s\n", dlerror());
    return 1;
  }

  char memory;
  ExampleClass* object = reinterpret_cast<ExampleClass*>(&memory);

  void (*f1)(ExampleClass*) = (void (*)(ExampleClass*)) dlsym(library, "_ZN12ExampleClassC1Ev");
  void (*f2)(ExampleClass*) = (void (*)(ExampleClass*)) dlsym(library, "_ZN12ExampleClassC2Ev");
  void (*f3)(ExampleClass*) = (void (*)(ExampleClass*)) dlsym(library, "_ZN12ExampleClassD1Ev");
  void (*f4)(ExampleClass*) = (void (*)(ExampleClass*)) dlsym(library, "_ZN12ExampleClassD2Ev");
  int (*f5)(ExampleClass*, int, bool) =
    (int (*)(ExampleClass*, int, bool)) dlsym(library, "_ZN12ExampleClass5PrintEib");

  printf("(1)\n");
  f1(object);
  printf("(2)\n");
  f2(object);
  printf("(3)\n");
  f3(object);
  printf("(4)\n");
  f4(object);
  printf("(5)\n");
  f5(object, 1, false);
  printf("(6)\n");

  dlclose(library);
  return 0;
}
