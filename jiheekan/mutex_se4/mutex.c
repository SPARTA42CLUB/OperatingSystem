#include <stdio.h>
#include <pthread.h>

int sharedVariable = 0;
pthread_mutex_t mutex;

void* increment(void* threadID) {
    int tid = (int)threadID;
    for (int i = 0; i < 5; ++i) {
        // 뮤텍스 락 획득
        pthread_mutex_lock(&mutex);

        // 공유 변수 수정
        sharedVariable++;

        // 뮤텍스 락 해제
        pthread_mutex_unlock(&mutex);
    }
    printf("Thread %d finished!\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int rc;

    // 뮤텍스 초기화
    pthread_mutex_init(&mutex, NULL);

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

    // 뮤텍스 제거
    pthread_mutex_destroy(&mutex);

    // 최종 결과 출력
    printf("The value of sharedVariable: %d\n", sharedVariable);

    return 0;
}
