#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

int shared_variable = 0; // 공유 변수
pthread_mutex_t mutex;   // 뮤텍스 선언

void* thread_function(void* arg) {
    int thread_id = *((int*)arg);

    // 공유 변수에 대한 안전한 접근을 위해 뮤텍스 락
    pthread_mutex_lock(&mutex);

    // 공유 변수 수정
    shared_variable += thread_id;

    // 공유 변수 출력
    printf("Thread ID: %d, Shared Variable: %d\n", thread_id, shared_variable);

    // 뮤텍스 언락
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // 뮤텍스 초기화
    pthread_mutex_init(&mutex, NULL);

    // 스레드 생성 및 실행
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
    }

    // 모든 스레드의 실행이 종료될 때까지 대기
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 뮤텍스 해제
    pthread_mutex_destroy(&mutex);

    return 0;
}

