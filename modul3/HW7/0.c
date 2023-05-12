#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>

extern size_t read_data_and_count(size_t N, int in[N])
{
    size_t total_read_count = 0;

    int epoll_fd = epoll_create(N);

    for (size_t i = 0; i < N; ++i) {
        // Неблокирующий ввод-вывод
        int flags = fcntl(in[i], F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(in[i], F_SETFL, flags);

        struct epoll_event new_epoll_event = {.events = EPOLLIN,
                                              .data.fd = in[i]};

        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, in[i], &new_epoll_event);
    }

    size_t epoll_fds = N;
    struct epoll_event events[N];
    while (epoll_fds) {
        int new_events_count = epoll_wait(epoll_fd, events, epoll_fds, -1);

        char temp_buffer[4096];
        for (size_t i = 0; i < new_events_count; ++i) {
            if (events[i].events & EPOLLIN) {
                ssize_t read_result = 0;
                while ((read_result =
                            read(events[i].data.fd, temp_buffer, 4096)) > 0) {
                    total_read_count += read_result;
                }

                if (read_result == -1 && errno == EAGAIN) {

                } else if (read_result == 0) {
                    // EOF

                    epoll_ctl(
                        epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, &events[i]);
                    close(events[i].data.fd);
                    --epoll_fds;

                } else {
                    perror("Unhandled read");
                }
            }
        }
    }

    // Закрываем epoll
    close(epoll_fd);

    return total_read_count;
}
