#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 자식 프로세스인 경우

        // 실행할 프로그램과 인수들을 배열로 정의
        char *args[] = {"ls", "-l", NULL};

        // execve를 사용하여 새로운 프로그램 실행
        if (execve("/bin/ls", args, NULL) == -1) {
            // execve 실행 실패 시 오류 메시지 출력
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        // 부모 프로세스인 경우

        // 자식 프로세스가 종료될 때까지 대기
        wait(NULL);
        printf("자식 프로세스가 종료되었습니다.\n");
    }

    return 0;
}
