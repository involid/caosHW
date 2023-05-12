#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFF_SIZE 4096

int main(int argc, char *argv[]) {
    char *hostname = argv[1];
    char *filepath = argv[2];

    struct addrinfo addr_hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
    struct addrinfo *addr_result = NULL;
    int rv = getaddrinfo(hostname, "http", &addr_hints, &addr_result);
    if (rv != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockfd, addr_result->ai_addr, addr_result->ai_addrlen);

    char request[BUFF_SIZE];
    sprintf(request, 
            "GET %s HTTP/1.1\r\n"
            "Host: %s\r\n"
            "Connection: close\r\n\r\n",
            filepath, hostname);

    write(sockfd, request, strlen(request));

    char buffer[BUFF_SIZE];
	bzero(buffer, BUFF_SIZE);
    int readed;
    int content_start = -1;
    
    while ((readed = read(sockfd, buffer, BUFF_SIZE)) > 0) {
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
    close(sockfd);

    return 0;
}
