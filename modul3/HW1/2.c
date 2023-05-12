#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

struct thread_task {
    int fd;
    int number;
};

void* ping(void* arg)
{
    int socket_fd = ((struct thread_task*)arg)->fd;
    int number = ((struct thread_task*)arg)->number;

    // first shot
    number -= 3;
    printf("%d\n", number);
    write(socket_fd, &number, sizeof(number));
    if (number == 0 || number > 100) {
        return 0;
    }

    while (1) {
        // take
        read(socket_fd, &number, sizeof(number));
        if (number == 0 || number > 100) {
            break;
        }
        number -= 3;
        printf("%d\n", number);
        // give
        write(socket_fd, &number, sizeof(number));
        if (number == 0 || number > 100) {
            break;
        }
    }
    return 0;
}

void* pong(void* arg)
{
    int socket_fd = *(int*)arg;
    int number;
    while (1) {
        // take
        read(socket_fd, &number, sizeof(number));
        if (number == 0 || number > 100) {
            break;
        }
        number += 5;
        printf("%d\n", number);
        // give
        write(socket_fd, &number, sizeof(number));
        if (number == 0 || number > 100) {
            return 0;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int number;
    if (argc <= 1) {
        perror("arg count");
    }
    sscanf(argv[1], "%d", &number);

    int fd[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fd) == -1) {
        perror("socketpair");
    }

    struct thread_task ping_task = {.fd = fd[0], .number = number};

    pthread_t ping_thread;
    int return_code = pthread_create(&(ping_thread), NULL, ping, &(ping_task));
    if (return_code != 0) {
        perror("pthread_create");
    }

    pthread_t pong_thread;
    return_code = pthread_create(&(pong_thread), NULL, pong, &(fd[1]));
    if (return_code != 0) {
        perror("pthread_create");
    }

    void* tmp;
    return_code = pthread_join(ping_thread, &tmp);
    if (return_code != 0) {
        perror("pthread_join");
    }

    return_code = pthread_join(pong_thread, &tmp);
    if (return_code != 0) {
        perror("pthread_join");
    }

    if (close(fd[0]) == -1) {
        perror("close");
    }
    if (close(fd[1]) == -1) {
        perror("close");
    }
    return 0;
}