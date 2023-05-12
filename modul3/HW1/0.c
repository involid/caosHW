#include <pthread.h>
#include <stdio.h>

void* recursive_read(void* arg)
{
    int number = 0;

    // Проверяем, можем ли мы прочитать число
    if (scanf("%d", &number) != EOF) {
        pthread_t new_thread;

        // Создаём новый поток, в котором попытаемся прочитать следующее число
        int return_code =
            pthread_create(&new_thread, NULL, recursive_read, NULL);
        if (return_code != 0)
            perror("pthread_create");

        // Ожидаем завершение только что созданного потока
        return_code = pthread_join(new_thread, NULL);
        if (return_code != 0)
            perror("pthread_join");

        printf("%d ", number);
    }
}

int main(int argc, char* argv[])
{
    // Вызовем из главного потока рекурсивную функцию чтения чисел
    recursive_read(NULL);

    return 0;
}
