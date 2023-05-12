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
        //close(socket_fd);
        //close(epoll_fd);
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
                                          .data.fd = epoll_fd};
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &epoll_event);

    struct epoll_event events[MAX_EVENTS];


    ////
	int new_events, sock_conn_fd, epollfd;
    epollfd = epoll_fd;
    int sock_listen_fd = socket_fd;
	char buffer[MAX_MESSAGE_LEN];
	memset(buffer, 0, sizeof(buffer));
    ////
    while (1) {
        if (terminate) {
            break;
        }
        working = 1;

        new_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		
		if (new_events == -1)
		{
			perror("Error in epoll_wait..\n");
		}

		for (int i = 0; i < new_events; ++i)
		{
            //printf("\n\n\n\ninsh vor ban\n\n\n\n\n");
			if (events[i].data.fd == sock_listen_fd)
			{
				sock_conn_fd = accept(sock_listen_fd, NULL, NULL);
                int flags = fcntl(sock_conn_fd, F_GETFL);
                flags |= O_NONBLOCK;
                fcntl(sock_conn_fd, F_SETFL, flags);

				if (sock_conn_fd == -1)
				{
					perror("Error accepting new connection..\n");
				}

				epoll_event.events = EPOLLIN | EPOLLET;
				epoll_event.data.fd = sock_conn_fd;
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sock_conn_fd, &epoll_event) == -1)
				{
					perror("Error adding new event to epoll..\n");
				}
			}
			else
			{
				int newsockfd = events[i].data.fd;
				int bytes_received = recv(newsockfd, buffer, MAX_MESSAGE_LEN, 0);
                //printf("aaaaa mors areeev %d\n", bytes_received);
				if (bytes_received <= 0)
				{
					epoll_ctl(epollfd, EPOLL_CTL_DEL, newsockfd, NULL);
					shutdown(newsockfd, SHUT_RDWR);
				}
				else
				{
					send(newsockfd, buffer, bytes_received, 0);
				}
			}
		}

        working = 0;
    }
    close(socket_fd);
    close(epoll_fd);
    return 0;
}