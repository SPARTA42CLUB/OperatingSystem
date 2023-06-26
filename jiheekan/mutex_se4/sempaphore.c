#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int sharedVariable = 0;
sem_t semaphore;

void* increment(void* threadID) {
    int tid = (int)threadID;
    for (int i = 0; i < 5; ++i) {
        // 세마포어 대기
        sem_wait(&semaphore);

        // 공유 변수 수정
        sharedVariable++;
        printf("Thread %d: sharedVariable = %d\n", tid, sharedVariable);

        // 세마포어 신호
        sem_post(&semaphore);
    }
    printf("Thread %d finished!\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int rc;

    // 세마포어 초기화
    sem_init(&semaphore, 0, 1);

    // 스레드 생성
    for (int t = 0; t < 2; t++) {
        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, increment, (void*)t);
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            return -1;
        }
    }

    // 모든 스레드의 실행 완료 대기
    for (int t = 0; t < 2; t++) {
        pthread_join(threads[t], NULL);
    }

    // 세마포어 제거
    sem_destroy(&semaphore);

    // 최종 결과 출력
    printf("The value of sharedVariable: %d\n", sharedVariable);

    return 0;
}
