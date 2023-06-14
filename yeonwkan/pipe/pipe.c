#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    pid_t pid;
    char write_msg[BUFFER_SIZE] = "Hello, Pipe!";
    char read_msg[BUFFER_SIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid > 0) {  // 부모 프로세스
        close(pipefd[0]);  // 읽기용 파이프 닫기

        write(pipefd[1], write_msg, strlen(write_msg) + 1);  // 파이프에 데이터 쓰기
        close(pipefd[1]);  // 쓰기용 파이프 닫기

        printf("Parent process sent message: %s\n", write_msg);
    } else {  // 자식 프로세스
        close(pipefd[1]);  // 쓰기용 파이프 닫기

        read(pipefd[0], read_msg, sizeof(read_msg));  // 파이프에서 데이터 읽기
        close(pipefd[0]);  // 읽기용 파이프 닫기

        printf("Child process received message: %s\n", read_msg);
    }

    return 0;
}
