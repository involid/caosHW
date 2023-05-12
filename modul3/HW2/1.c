#include <error.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool is_prime(int64_t number)
{
    if (number == 0 || number == 1 || number == -1)
        return false;
    if (number < 0)
        number = -number;

    for (int div = 2; div * div <= number; ++div) {
        if (number % div == 0)
            return false;
    }
    return true;
}

struct thread_task {
    int64_t left_bound;
    int64_t prime;
    int32_t num;
    bool ready_to_print;
    bool waiting_to_print;
    pthread_mutex_t* mutex;
    pthread_cond_t* cv1;
    pthread_cond_t* cv2;
};

void* prime_generator(void* args)
{
    struct thread_task* task = (struct thread_task*)args;

    for (int32_t i = 0; i < task->num; ++i) {
        pthread_mutex_lock(task->mutex);

        while (!(task->ready_to_print)) {
            pthread_cond_wait(task->cv2, task->mutex);
        }
        task->ready_to_print = false;

        while (!is_prime(task->left_bound)) {
            ++(task->left_bound);
        }
        (task->prime) = (task->left_bound);
        ++(task->left_bound);

        task->waiting_to_print = true;
        pthread_cond_signal(task->cv1);

        pthread_mutex_unlock(task->mutex);
    }
}

int main(int argc, char* argv[])
{
    int64_t left_bound = (int64_t)strtol(argv[1], NULL, 10);
    int64_t right_bound = (int64_t)strtol(argv[2], NULL, 10);
    int32_t num = (int32_t)strtol(argv[3], NULL, 10);

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_t prime_generator_thread;
    pthread_cond_t cv1 = PTHREAD_COND_INITIALIZER;
    pthread_cond_t cv2 = PTHREAD_COND_INITIALIZER;

    struct thread_task* task =
        (struct thread_task*)calloc(1, sizeof(struct thread_task));
    task->mutex = &mutex;
    task->left_bound = left_bound;
    task->cv1 = &cv1;
    task->cv2 = &cv2;
    task->ready_to_print = false;
    task->waiting_to_print = false;
    task->num = num;

    pthread_create(
        &prime_generator_thread, NULL, &prime_generator, (void*)task);

    for (int i = 0; i < num; ++i) {
        pthread_mutex_lock(&mutex);

        task->ready_to_print = true;
        pthread_cond_signal(&cv2);

        while (!(task->waiting_to_print)) {
            pthread_cond_wait(&cv1, &mutex);
        }
        printf("%ld\n", task->prime);
        task->waiting_to_print = false;

        pthread_mutex_unlock(&mutex);
    }

    pthread_join(prime_generator_thread, NULL);
    pthread_mutex_destroy(&mutex);
    free(task);
    return 0;
}