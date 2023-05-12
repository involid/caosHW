#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static sig_atomic_t not_terminate = 1;
static sig_atomic_t is_blocked = 0;

FILE* x;

void handler(int signum)
{
    fclose(x);
    if (signum == SIGTERM || signum == SIGINT) {
        if (!is_blocked) {
            not_terminate = 0;
        } else {
            exit(0);
        }
    }
}


const char QUERY[] = "GET %s HTTP/1.1";
const char OK[] = "HTTP/1.1 200 OK\n";
const char NOT_FOUND[] = "HTTP/1.1 404 Not Found\n";
const char FORBIDDEN[] = "HTTP/1.1 403 Forbidden\n";

const int BUFF_SIZE = 4096;


int main(int argc, char* argv[]) {
    x = fopen("x.txt", "w");
    struct sigaction act;
    act.sa_handler = handler;
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);

    int port = atoi(argv[1]);
    char* file_path = argv[2];
    strcat(file_path, "/");

    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct in_addr input_address;
    input_address.s_addr = inet_addr("127.0.0.1");
    struct sockaddr_in socket_ipv4_address = {.sin_family = AF_INET,
                                              .sin_port = htons(port), 
                                              .sin_addr = input_address};

    int bind_result = bind(socket_fd, (struct sockaddr *)&socket_ipv4_address, sizeof(socket_ipv4_address));
    if (bind_result == -1) perror("bind");

    int listen_result = listen(socket_fd, SOMAXCONN);
    if (listen_result == -1) perror("listen");

    while (not_terminate) {
        is_blocked = 1;
        int client_fd = accept(socket_fd, NULL, NULL);
        is_blocked = 0;
        FILE* client_file = fdopen(client_fd, "r");
        char file_name[BUFF_SIZE];
        memset(file_name, '\0', BUFF_SIZE);
        fscanf(client_file, QUERY, file_name);

        char full_file_name[BUFF_SIZE];
        memset(full_file_name, '\0', BUFF_SIZE);
        memcpy(full_file_name, file_path, strlen(file_path));
        strcat(full_file_name, "/");
        strcat(full_file_name, file_name);

        ///
        fprintf(x, "%s\n", full_file_name);
        fprintf(x, "%d\n", access(full_file_name, R_OK));
        ///

        if (access(full_file_name, F_OK) != 0) {
            write(client_fd, NOT_FOUND, strlen(NOT_FOUND));
        }
        else if (access(full_file_name, R_OK) != 0) {
            write(client_fd, FORBIDDEN, strlen(FORBIDDEN));
        }
        else {
            write(client_fd, OK, strlen(OK));
            FILE* input_file = fopen(full_file_name, "r");

            fseek(input_file, 0, SEEK_END);
            size_t file_size = ftell(input_file);
            char size_str[50];
            sprintf(size_str, "Content-Length: %ld\n\n", file_size);
            write(client_fd, size_str, strlen(size_str));

            rewind(input_file);
            char buffer[BUFF_SIZE];
            size_t scanned;
            while ((scanned = fread(buffer, 1, BUFF_SIZE, input_file))) {
                write(client_fd, buffer, scanned);
            }
            fclose(input_file);
        }
        fclose(client_file);
        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
    }
    close(socket_fd);
    return 0;
}