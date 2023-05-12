#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFF_SIZE 4096

off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) != 0)
        perror("stat");
    
    return st.st_size;
}

int main(int argc, char *argv[]) {
    char* server_name = argv[1];
    char* script_path = argv[2];
    char* file_name = argv[3];

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket");
    }

    struct addrinfo addr_hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
    struct addrinfo *addr_result = NULL;
    int rv = getaddrinfo(server_name, "http", &addr_hints, &addr_result);
    if (rv != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    }

    if (connect(socket_fd, addr_result->ai_addr, addr_result->ai_addrlen) != 0) {
        perror("connect");
    }
    
    char request[BUFF_SIZE];
    off_t file_size = fsize(file_name);
    sprintf(request, "POST %s HTTP/1.0\r\n"
                     "Host: %s\r\n"
                     "Content-Type: application/octet-stream\r\n"
                     "Content-Length: %ld\r\n\r\n",
                      script_path, server_name, file_size);

    if (write(socket_fd, request, strlen(request)) < 0) {
        perror("write");
    }

    // send file
    int file_fd = open(file_name, O_RDONLY);
    if (file_fd < 0) {
        perror("open");
    }

    ssize_t readed;
    while ((readed = read(file_fd, request, BUFF_SIZE)) > 0) {
        if (send(socket_fd, request, readed, 0) < 0) {
            perror("send");
        }
    }
    close(file_fd);

    char buffer[BUFF_SIZE];
	bzero(buffer, BUFF_SIZE);
    int content_start = -1;
    
    while ((readed = read(socket_fd, buffer, BUFF_SIZE)) > 0) {
        if (content_start == -1) {
            char* content = strstr(buffer, "\r\n\r\n");
            if (content != NULL) {
                content_start = content - buffer + sizeof("\r\n\r\n");
                printf("%s", (buffer + content_start - 1));
            }
        } else {
            printf("%s", buffer);
        }
	    bzero(buffer, BUFF_SIZE);
    }
    
    close(socket_fd);

    return 0;
}