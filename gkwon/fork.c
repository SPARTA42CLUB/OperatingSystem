#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // 새로운 프로세스 생성

    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        return 1;
    } else if (pid == 0) {
        // 자식 프로세스인 경우
        printf("Child process: PID = %d\n", getpid());

        // 새로운 프로그램 실행
        char *args[] = {"ls", "-al", NULL};  // 실행할 프로그램과 인자
        execvp(args[0], args);

        // execvp 함수가 성공적으로 실행되지 않은 경우에만 아래 코드가 실행됨
        fprintf(stderr, "execvp failed\n");
        return 1;
    } else {
        // 부모 프로세스인 경우
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);

        // 자식 프로세스의 종료를 대기
        wait(NULL);
        printf("Child process terminated\n");
    }

    return 0;
}
