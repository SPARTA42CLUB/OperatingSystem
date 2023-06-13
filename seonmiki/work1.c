#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // 자식 프로세스 생성

    if (pid == -1) {
        // fork 실패
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // 자식 프로세스
        printf("자식 프로세스입니다.\n");

        // exec 함수로 다른 프로그램 실행
        char *args[] = {"/bin/ls", "-l", NULL};
        execv(args[0], args);

        // exec 함수가 성공하지 못한 경우에만 아래 코드가 실행됨
        perror("execv");
        return 1;
    } else {
        // 부모 프로세스
        printf("부모 프로세스입니다.\n");

        // 자식 프로세스의 종료를 기다림
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("자식 프로세스가 정상적으로 종료되었습니다. 종료 상태: %d\n", exit_status);
        } else if (WIFSIGNALED(status)) {
            int term_signal = WTERMSIG(status);
            printf("자식 프로세스가 시그널에 의해 종료되었습니다. 시그널 번호: %d\n", term_signal);
        }
    }

    return 0;
}
