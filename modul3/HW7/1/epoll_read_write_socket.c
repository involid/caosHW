#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <netinet/in.h>

#define MAX_EVENTS 128
#define MAX_MESSAGE_LEN 4096

static sig_atomic_t terminate = 0;
static sig_atomic_t working = 0;

int socket_fd;
int epoll_fd;
void sig_handler() {
    if (!working) {
        close(socket_fd);
        close(epoll_fd);
        exit(0);
    }
    terminate = 1;
}

void make_upper(char* arr, size_t size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] >= 'a' && arr[i] <= 'z') {
            arr[i] += 'A' - 'a';
        }
    }
}

int main(int argc, char* argv[]) {
    //handling SIGTERM signal
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGTERM, &act, NULL);

    int port = atoi(argv[1]);
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // Create server's socket address
    struct sockaddr_in socket_ipv4_address = {.sin_family = AF_INET,
                                              .sin_port = htons(port), 
                                              .sin_addr = inet_addr("127.0.0.1")};

    // Assign address to socket
    int bind_result = bind(socket_fd, (struct sockaddr *)&socket_ipv4_address, sizeof(socket_ipv4_address));
    if (bind_result == -1) perror("bind");

    // Incoming connections queue
    int listen_result = listen(socket_fd, SOMAXCONN);
    if (listen_result == -1) perror("listen");

    epoll_fd = epoll_create(MAX_EVENTS);

    struct epoll_event epoll_event = {.events = EPOLLIN,
                                      .data.fd = socket_fd};
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &epoll_event);

    struct epoll_event events[MAX_EVENTS];
    while (1) {
        if (terminate) {
            break;
        }
        working = 1;

        int new_events_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (new_events_count == -1) {
            perror("epoll_wait");
        }

        for (int i = 0; i < new_events_count; ++i) {
            if (events[i].data.fd == socket_fd) {
                //accepting new connection
                int client_fd = accept(socket_fd, NULL, NULL);
                if (client_fd == -1) {
                    perror("accepting client");
                }

                int flags = fcntl(client_fd, F_GETFL);
                flags |= O_NONBLOCK;
                fcntl(client_fd, F_SETFL, flags);

                struct epoll_event new_epoll_event = {.events = EPOLLIN | EPOLLET,
                                                      .data.fd = client_fd};
                int rv = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &new_epoll_event);
                if (rv == -1) {
                    perror("adding new client");
                }

            }
            else {
                //reading and writing message
                if (!(events[i].events & EPOLLIN)) {
                    perror("Unhandled read");
                }
                int curr_fd = events[i].data.fd;
                char buff[MAX_MESSAGE_LEN];
                int readed = read(curr_fd, buff, MAX_MESSAGE_LEN);
                if (readed == 0) {
                    //EOF
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, curr_fd, &events[i]);
                    shutdown(curr_fd, SHUT_RDWR);
                    close(curr_fd);
                }
                else if (readed > 0) {
                    make_upper(buff, readed);
                    write(curr_fd, buff, readed);
                }
                else if (readed == -1 && errno == EAGAIN) {
                    //nothing readed
                }
                else {
                    perror("read from client");
                }
            }
        }
        working = 0;
    }
    close(socket_fd);
    close(epoll_fd);
    return 0;
}