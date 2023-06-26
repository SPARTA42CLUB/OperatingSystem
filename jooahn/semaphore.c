#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 2

sem_t* semaphore;    // 세마포어 포인터 선언

void* thread_function(void* arg) {
    int thread_id = *((int*)arg);

    for (int i = 0; i < 5; i++) {
        sem_wait(semaphore);    // 세마포어 대기

        printf("Thread ID: %d, Count: %d\n", thread_id, i);

        sem_post(semaphore);    // 세마포어 신호
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    semaphore = sem_open("/my_semaphore", O_CREAT, 0644, 1);    // 세마포어 생성

    // 스레드 생성 및 실행
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
    }

    // 모든 스레드의 실행이 종료될 때까지 대기
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_close(semaphore);    // 세마포어 닫기
    sem_unlink("/my_semaphore");    // 세마포어 삭제

    return 0;
}

