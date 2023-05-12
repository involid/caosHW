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
        "I had a sort of presentiment of it: all last night I dreamt about a pair of monstrous "
        "rats. Upon my word, I never saw the like of 'em—so black and enormous. ";
    char* SEND_string_2 =
        "They came, and snuffed about, and vanished... "
        "Here's a letter which I will read you from Andrei Ivanovich Chmikov.\n";
    char* SEND_string_3 =
        "You know him, Artemi Philippovich (to the CHARITY COMMISSIONER).\n";

    sleep(1);
    write(socket_fd, SEND_string_1, strlen(SEND_string_1));
    sleep(3);
    write(socket_fd, SEND_string_2, strlen(SEND_string_2));
    sleep(1);
    write(socket_fd, SEND_string_3, strlen(SEND_string_3));
    // sleep(1);

    // Closing the connection and socket
    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);

    return 0;
}
