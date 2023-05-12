#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("argc == %d\n", argc);
    for (int i = 0; i < argc; ++i) {
        printf("%s\n", argv[i]);
    }
}

/***
    gcc test_arg.c -o test_arg
    ./test_arg abra shvabra cadabra

    argc == 4
    ./test_arg
    abra
    shvabra
    cadabra
***/
