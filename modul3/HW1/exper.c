#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* count_sum(void* arg) {
    int64_t result = 0;
    int64_t number = 0;
    //while (scanf("%ld", &number) != EOF) {
    //    result += number;
    //}
    return (void*)result;
}

int main(int argc, char* argv[]) {
    //int64_t number;
    //sscanf(argv[1], "%d", &number);

    pthread_attr_t attr;
    int rc = pthread_attr_init(&attr);

    pthread_t thread, t2, t3;
    pthread_create(&thread, &attr, count_sum, NULL);
    pthread_create(&t2, &attr, count_sum, NULL);
    pthread_create(&t3, &attr, count_sum, NULL);
    rc = pthread_join(thread, NULL);
    rc = pthread_join(t2, NULL);
    rc = pthread_join(t3, NULL);
    return 0;
}