#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shared_memory_example", 1234); // 공유 메모리 식별자 생성

    // 공유 메모리 생성
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // 공유 메모리를 현재 프로세스의 주소 공간에 첨부
    void* shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void*)-1) {
        perror("shmat");
        return 1;
    }

    // 부모 프로세스와 자식 프로세스 간에 데이터를 공유하기 위한 정수 포인터
    int* shared_data = (int*)shmaddr;

    pid_t pid = fork(); // 자식 프로세스 생성

    if (pid == -1) {
        // fork 실패
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // 자식 프로세스
        printf("자식 프로세스입니다.\n");

        // 공유 메모리에 정수 데이터 저장
        *shared_data = 42;
        printf("자식 프로세스에서 데이터 %d를 공유 메모리에 저장했습니다.\n", *shared_data);

        // 공유 메모리에서 첨부 해제
        if (shmdt(shmaddr) == -1) {
            perror("shmdt");
            return 1;
        }

        return 0;
    } else {
        // 부모 프로세스
        printf("부모 프로세스입니다.\n");

        // 자식 프로세스가 공유 메모리에 저장한 데이터를 읽음
        sleep(1); // 자식 프로세스가 먼저 실행되도록 대기
        printf("부모 프로세스에서 공유 메모리에서 데이터 %d를 읽었습니다.\n", *shared_data);

        // 공유 메모리에서 첨부 해제
        if (shmdt(shmaddr) == -1) {
            perror("shmdt");
            return 1;
        }

        // 공유 메모리 삭제
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            return 1;
        }

        return 0;
    }
}
