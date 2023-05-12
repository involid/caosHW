#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

size_t READ_COUNT = 4096;

int main(int argc, char* argv[]) {
    int input_fd = open(argv[2], O_RDONLY);
    if (input_fd == -1) perror("open");

    int pipefd[2];
    int pipe_result = pipe(pipefd);
    if (pipe_result != 0) perror("pipe");

    pid_t child_pid = fork();
    if (child_pid == 0) {
        // ===== Дочерний процесс =====

        // Закрываем ненужный дескриптор на чтение из пайпа
        int close_result = close(pipefd[0]);
        if (close_result == -1) perror("close");

        // Мы хотим, чтобы процесс писал не на поток вывода, а в пайп
        // Создаём копию pipefd[1] с номером 1 (STDOUT_FILENO)
        int dup2_result = dup2(pipefd[1], STDOUT_FILENO);
        if (dup2_result == -1) perror("dup2");

        // Закрываем pipefd[1], у нас есть копия с номером 1 (STDOUT_FILENO)
        close_result = close(pipefd[1]);
        if (close_result == -1) perror("close");

        // Мы хотим, чтобы процесс читал не из потока ввода, а из файла
        // Создаём копию input_fd с номером 0 (STDIN_FILENO)
        dup2_result = dup2(input_fd, STDIN_FILENO);
        if (dup2_result == -1) perror("dup2");
        
        // Закрываем input_fd, у нас есть копия с номером 0 (STDIN_FILENO)
        close_result = close(input_fd);
        if (close_result == -1) perror("close");

        execlp(argv[1], argv[1], NULL);
        perror("exec");

    } else if (child_pid > 0) {
        // ===== Родительский процесс =====

        // Закрываем ненужный дескриптор на запись в пайп
        int close_result = close(pipefd[1]);
        if (close_result == -1) perror("close");

        ssize_t answer = 0;

        int read_buffer[READ_COUNT];
        ssize_t read_result = 0;
        do {
            read_result = read(pipefd[0], read_buffer, READ_COUNT);
            if (read_result == -1) perror("read");

            answer += read_result;

        } while (read_result != 0);

        int wstatus = 0;
        int waitpid_result = waitpid(child_pid, &wstatus, 0);
        if (waitpid_result == -1) perror("waitpid");

        printf("%zd", answer);

    } else {
        perror("fork");
    }
    
    return 0;
}
