#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>

const char* ok_message = "HTTP/1.1 200 OK\r\n";
const char* forbidden_message = "HTTP/1.1 403 Forbidden\r\n\r\n";
const char* not_found_message = "HTTP/1.1 404 Not Found\r\n\r\n";

const size_t max_digit = 11;
const size_t buff_size = 1024;
const size_t file_name_max_size = 256;
char buff[1024];

static sig_atomic_t terminate = 0;
static sig_atomic_t working = 0;

//FILE* x;

int socket_fd;
void sig_handler() {
    //fclose(x);
    if (!working) {
        close(socket_fd);
        exit(0);
    }
    terminate = 1;
}

int main(int argc, char* argv[]) {
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    int port = atoi(argv[1]);

    ///
    //x = fopen("x.txt", "w");
    //fprintf(x, "%d\n", port);
    ///

    const char* path_to_dir = argv[2];

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

    while (1) {
        if (terminate) {
            return 0;
        }
        // Get client socket
        int client_fd = accept(socket_fd, NULL, NULL);
        working = 1;

        // read_request
        //bzero(buff, buff_size);
        read(client_fd, buff, buff_size);

        size_t file_name_sz = 0;
        for (int i = sizeof("GET ") - 1; i < buff_size; ++i) {
            if (buff[i] == ' ') {
                break;
            }
            ++file_name_sz;
        }
        char file_name[file_name_max_size];
        bzero(file_name, file_name_max_size);
        memcpy(file_name, buff + sizeof("GET ") - 1, file_name_sz);

        dup2(socket_fd, STDIN_FILENO);
        int c;
        while ((c = getchar()) != EOF) {
            if (c == '\r') {
                c = getchar();
                if (c == '\n' || c == EOF) {
                    break;
                }
            }
        }

        // send_response
        char filepath[file_name_max_size];
        bzero(filepath, file_name_max_size);
        strcat(filepath, path_to_dir);
        strcat(filepath, "/");
        strcat(filepath, file_name);

        //fprintf(x, "%s\n", file_name);
        //fprintf(x, "%s \n", filepath);

        if (access(filepath, R_OK) == 0) {
            write(client_fd, ok_message, strlen(ok_message));
            struct stat st;
            stat(filepath, &st);
            char size[max_digit];
            bzero(size, max_digit);
            sprintf(size, "%ld", st.st_size);

            write(client_fd, "Content-Length: ", sizeof("Content-Length: ") - 1);
            write(client_fd, size, strlen(size));
            write(client_fd, "\r\n\r\n", sizeof("\r\n\r\n") - 1);
            FILE* file = fopen(filepath, "r");
            
            int readed = 0;
            while ((readed = fread(buff, 1, buff_size, file)) > 0) {
                write(client_fd, buff, readed);
            }

            fclose(file);
        }
        else if (access(filepath, F_OK) == 0) {
            write(client_fd, forbidden_message, strlen(forbidden_message));
        }
        else {
            write(client_fd, not_found_message, strlen(not_found_message));
        }
        
        // Say goodbye to ciient and close connection
        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
        working = 0;
    }

    // Close server
    close(socket_fd);

    return 0;
}