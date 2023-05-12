#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    const char* ip_str = argv[1];
    in_addr_t ip = inet_addr(ip_str);

    const char* port_str = argv[2];
    uint16_t port = htons(strtol(port_str, NULL, 10));

    // Создаём сокет
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Инициализируем структуру для подключения к серверу
    struct sockaddr_in ipv4_addr = {
        .sin_family = AF_INET, .sin_port = port, .sin_addr = ip};

    // Подключаемся к серверу
    connect(socket_fd, (struct sockaddr*)&ipv4_addr, sizeof(ipv4_addr));

    int32_t number = 0;
    while (scanf("%d", &number) != EOF) {
        // Отправляем серверу число
        write(socket_fd, &number, sizeof(number));

        // Получаем число в ответ
        int read_result = read(socket_fd, &number, sizeof(number));

        if (read_result == 0) {
            break;

        } else {
            printf("%d\n", number);
        }
    }

    // Закрываем соединение и сокет
    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);

    return 0;
}