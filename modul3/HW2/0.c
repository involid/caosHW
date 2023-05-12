#include <error.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct thread_task {
  double *buffer;
  int position;
  int iterations;
  int buffer_size;

  pthread_mutex_t *mutex;
};

void *manipulate_cell(void *arg) {
  struct thread_task *task = (struct thread_task *)arg;

  for (int i = 0; i < task->iterations; ++i) {

    pthread_mutex_lock(task->mutex);
    int right_pos = (task->position + 1) % (task->buffer_size);
    int left_pos = (task->position - 1) >= 0
                       ? (task->position - 1)
                       : (task->position + task->buffer_size - 1);
    (task->buffer)[right_pos] += 1.01;
    (task->buffer)[left_pos] += 0.99;
    ++(task->buffer)[task->position];
    pthread_mutex_unlock(task->mutex);
  }

  free(task);
}

int main(int argc, char *argv[]) {
  int N = (int)strtol(argv[1], NULL, 10);
  int k = (int)strtol(argv[2], NULL, 10);

  double double_number = 0.0;
  double *numbers = (double *)calloc(k, sizeof(double_number));

  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  pthread_t threads[k];
  for (int i = 0; i < k; ++i) {
    pthread_t new_thread;

    struct thread_task *task =
        (struct thread_task *)calloc(1, sizeof(struct thread_task));
    task->buffer = numbers;
    task->position = i;
    task->iterations = N;
    task->buffer_size = k;
    task->mutex = &mutex;

    int return_code =
        pthread_create(&new_thread, NULL, &manipulate_cell, (void *)task);
    if (return_code != 0)
      error(1, return_code, "pthread_create");

    threads[i] = new_thread;
  }

  for (int i = 0; i < k; ++i) {
    int return_code = pthread_join(threads[i], NULL);
    if (return_code != 0)
      error(1, return_code, "pthread_join");
  }

  for (int i = 0; i < k; ++i) {
    printf("%.10g\n", numbers[i]);
  }

  pthread_mutex_destroy(&mutex);

  free(numbers);

  return 0;
}
