#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // 공유 메모리의 크기

int main() {
    int shmid;
    key_t key;
    char *shmaddr;

    // 공유 메모리의 키 생성
    key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // 공유 메모리 생성
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // 공유 메모리에 연결
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // 부모 프로세스에서 데이터를 쓰기
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // 자식 프로세스는 공유 메모리에서 데이터를 읽기
        printf("Child process: Data read from shared memory: %s\n", shmaddr);
    } else {
        // 부모 프로세스는 공유 메모리에 데이터를 쓰기
        sprintf(shmaddr, "Hello, shared memory!");

        // 자식 프로세스의 종료를 대기
        wait(NULL);
    }

    // 공유 메모리와의 연결 해제
    shmdt(shmaddr);

    // 공유 메모리 삭제
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
