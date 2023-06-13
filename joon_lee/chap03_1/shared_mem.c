#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // 공유 메모리 크기

int main() {
    int shmid;  // 공유 메모리 식별자
    int *shared_value;  // 공유 메모리를 가리키는 포인터

    // 공유 메모리 생성
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // 공유 메모리를 현재 프로세스 주소 공간에 연결
    shared_value = (int *)shmat(shmid, NULL, 0);
    if (shared_value == (int *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // 공유 메모리에 초기값 설정
    *shared_value = 0;

    // 자식 프로세스 생성
    pid_t pid = fork();

    if (pid < 0) {
        // fork 실패 시 오류 메시지 출력
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 자식 프로세스인 경우

        // 공유 메모리의 값을 10번 읽고 증가시킴
        for (int i = 0; i < 10; i++) {
            printf("자식 프로세스: %d\n", *shared_value);
            (*shared_value)++;
            sleep(1);
        }

        // 자식 프로세스가 종료될 때 공유 메모리 연결 해제
        if (shmdt(shared_value) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }
    } else {
        // 부모 프로세스인 경우

        // 부모 프로세스도 공유 메모리의 값을 10번 읽고 증가시킴
        for (int i = 0; i < 10; i++) {
            printf("부모 프로세스: %d\n", *shared_value);
            (*shared_value)++;
            sleep(1);
        }

        // 부모 프로세스가 종료될 때 공유 메모리 연결 해제
        if (shmdt(shared_value) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }

        // 부모 프로세스가 종료될 때 공유 메모리 제거
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
