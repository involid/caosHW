#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Create server socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Create server's socket address
    struct sockaddr_in socket_ipv4_address = {.sin_family = AF_INET,
                                              .sin_port = htons(1337), 
                                              .sin_addr = inet_addr("127.0.0.1")};

    // Assign address to socket
    int bind_result = bind(socket_fd, /*(struct sockaddr *)*/&socket_ipv4_address, sizeof(socket_ipv4_address));
    if (bind_result == -1) perror("bind");

    // Incoming connections queue
    int listen_result = listen(socket_fd, SOMAXCONN);
    if (listen_result == -1) perror("listen");

    while (1) {
        // Get client socket
        int client_fd = accept(socket_fd, NULL, NULL);

        // read_request

        // send_response

        // Say goodbye to ciient and close connection
        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
    }

    // Close server
    close(socket_fd);

    return 0;
}
