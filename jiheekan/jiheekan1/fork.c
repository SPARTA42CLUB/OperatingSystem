#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    child_pid = fork(); // 자식 프로세스 생성

    if (child_pid == -1) {
        perror("fork"); // fork 실패 시 오류 메시지 출력
        exit(1);
    } else if (child_pid == 0) {
        // 자식 프로세스에서 실행할 코드
        execl("/bin/ls", "ls", "-l", NULL); // 예시로 ls 명령어 실행
        perror("execl"); // execl 실패 시 오류 메시지 출력
        exit(1);
    } else {
        // 부모 프로세스에서 실행할 코드
        wait(NULL); // 자식 프로세스의 종료를 기다림
        printf("자식 프로세스가 종료되었습니다.\n");
    }

    return 0;
}
