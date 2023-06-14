#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
    char message[] = "안녕, 자식 프로세스!";

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        // 부모 프로세스
        close(pipefd[0]);  // 사용하지 않는 읽기 닫기

        // 메시지를 파이프에 씀
        write(pipefd[1], message, strlen(message) + 1);
        printf("부모 프로세스: 자식에게 메시지를 전송했습니다.\n");

        close(pipefd[1]);  // 쓰기 닫기
    } else {
        // 자식 프로세스
        close(pipefd[1]);  // 사용하지 않는 쓰기 닫기

        // 파이프에서 메시지를 읽음
        read(pipefd[0], buffer, sizeof(buffer));
        printf("자식 프로세스: 받은 메시지: %s\n", buffer);

        close(pipefd[0]);  // 읽기 닫기
    }

    return 0;
}
