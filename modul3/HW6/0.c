#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    const char* port_str = argv[1];
    uint16_t port = htons(strtol(port_str, NULL, 10));

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in ipv4_addr = {
        .sin_family = AF_INET, .sin_port = port, .sin_addr = inet_addr("127.0.0.1")};

    int32_t number = 0;
    while (scanf("%d", &number) != EOF) {
	sendto(socket_fd, &number, sizeof(number), 0, (struct sockaddr*)&ipv4_addr, sizeof(ipv4_addr));

	bind(socket_fd, (struct sockaddr*)&ipv4_addr, sizeof(ipv4_addr));
	int return_result;
	recvfrom(socket_fd, &return_result, sizeof(return_result), 0, NULL, NULL);
        printf("%d\n", return_result);
    }
    close(socket_fd);

    return 0;
}