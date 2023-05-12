#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*function_t)(double);

int main(int argc, char* argv[]) {
    // Load library
    void* library = dlopen(argv[1], RTLD_LAZY);
    if (library == NULL) {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        exit(1);
    }

    // Get function from library
    void* function = dlsym(library, argv[2]);
    if (function == NULL) {
        fprintf(stderr, "dlsym error: %s\n", dlerror());
        exit(1);
    }

    double number = 0.0;
    while (scanf("%lf", &number) != EOF) {
        function_t f = (function_t)function;

        printf("%.3f ", f(number));
    }

    // Close library, now it's useless    
    dlclose(library);

    return 0;
}