#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dispatch/dispatch.h>

#define NUM_THREADS 5

dispatch_semaphore_t semaphore;
int critical = 0;

void* worker(void* arg) {
	int thread_id = *(int*)arg;

	printf("Thread %d: Waiting...\n", thread_id);
	dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);

	printf("Thread %d: Entered critical section.\n", thread_id);
	for (int i = 0; i < 10000; i++)
		++critical;
	printf("Thread %d: Exiting critical section.\n", thread_id);

	dispatch_semaphore_signal(semaphore);

	pthread_exit(NULL);
}

int main() {
	pthread_t threads[NUM_THREADS];
	int thread_ids[NUM_THREADS];

	// 세마포어 초기화
	semaphore = dispatch_semaphore_create(1);

	// 스레드 생성 및 실행
	for (int i = 0; i < NUM_THREADS; i++) {
		thread_ids[i] = i + 1;
		pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
	}

	// 모든 스레드 종료 대기
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("%d\n", critical);

	// 세마포어 해제
	dispatch_release(semaphore);

	return 0;
}
