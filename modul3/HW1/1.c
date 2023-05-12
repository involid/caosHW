#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* count_sum(void* arg) {
    int64_t result = 0;
    int64_t number = 0;
    while (scanf("%ld", &number) != EOF) {
        result += number;
    }
    return (void*)result;
}

int main(int argc, char *argv[]) {
    int64_t number;
    sscanf(argv[1], "%d", &number);

    pthread_t* threads = calloc(number, sizeof(pthread_t));
    for (int i = 0; i < number; ++i) {
        int return_code = pthread_create(&(threads[i]), NULL, count_sum, NULL);
        if (return_code != 0) perror("pthread_create");
    }

    int64_t result = 0;
    for (int i = 0; i < number; ++i) {
        void* tmp;
        int return_code = pthread_join(threads[i], &tmp);
        if (return_code != 0) perror("pthread_join");
        result += (int64_t)tmp;
    }

    printf("%d\n", result);
    return 0;
}
