#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024 // 공유 메모리 크기

int main() {
    int shmid;
    key_t key;
    char *shm_ptr;
    char message[] = "Hello, shared memory!";

    key = ftok(".", 'M'); // 키 생성

    // 공유 메모리 세그먼트 생성
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget"); // shmget 실패 시 오류 메시지 출력
        exit(1);
    }

    // 공유 메모리 연결
    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *) -1) {
        perror("shmat"); // shmat 실패 시 오류 메시지 출력
        exit(1);
    }

    // 공유 메모리에 데이터 쓰기
    strncpy(shm_ptr, message, sizeof(message));

    // 데이터 읽기
    printf("공유 메모리에서 읽은 메시지: %s\n", shm_ptr);

    // 공유 메모리 접근 종료
    shmdt(shm_ptr);

    // 공유 메모리 제거
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
