#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    const char* ip_str = argv[1];
    in_addr_t ip = inet_addr(ip_str);

    const char* port_str = argv[2];
    uint16_t port = htons(strtol(port_str, NULL, 10));

    // Creating a socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Initializing the structure for connecting to the server
    struct sockaddr_in ipv4_addr = {
        .sin_family = AF_INET, .sin_port = port, .sin_addr = ip};

    // Connecting to the server
    connect(socket_fd, (struct sockaddr*)&ipv4_addr, sizeof(ipv4_addr));

    char* SEND_string_1 =
        "Besides that, it doesn't do for the court chamber to get so full of rubbish of all sorts: "
        "why, there was a sporting whip lying among the papers on your very desk.";
    char* SEND_string_2 =
        " I know you're fond of sport, but there is a proper time and place for everything—when "
        "the Inspector is gone you can put it back again.";

    sleep(3);
    write(socket_fd, SEND_string_1, strlen(SEND_string_1));
    sleep(5);
    write(socket_fd, SEND_string_2, strlen(SEND_string_2));

    dup2(socket_fd, STDIN_FILENO);

    char c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }

    // Closing the connection and socket
    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);

    return 0;
}
