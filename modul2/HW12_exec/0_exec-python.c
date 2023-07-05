#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const size_t MAX_SIZE = 4096;

const char FORMAT_STRING[] = "print(%s)";

int main()
{
    char input[MAX_SIZE];
    char program[MAX_SIZE];

    fgets(input, sizeof(input), stdin);

    char* delimiter = strchr(input, '\n');
    if (delimiter != NULL) {
        *delimiter = '\0';
    }

    // Подготавливаем вход для интерпретатора python3
    snprintf(program, sizeof(program), FORMAT_STRING, input);

    // Подменяем текущую программу на интерпретатор
    // Обратите внимание: fork нам тут не нужен
    execlp("python3", "python3", "-c", program, NULL);

    // Если мы дошли до этой строчки, то exec не смог выполниться,
    // выводим ошибку
    perror("exec");

    // Возвращаем не 0, потому что выполнение не является успешным
    return 1;
}