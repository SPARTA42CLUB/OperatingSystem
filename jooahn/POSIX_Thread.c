#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

// thread function
void *func(void *threadID) {
	long tid = (long)threadID;
	printf("스레드 ID : %ld\n", tid);
	printf("스레드 실행 중...\n");

	printf("스레드 종료 : %ld\n", tid);
	pthread_exit(NULL);
}

int main() {
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;

	for (t = 0; t < NUM_THREADS; t++) {
		printf("main thread : thread %ld 생성 \n", t);
		rc = pthread_create(&threads[t], NULL, func, (void *)t);
		if (rc) {
			printf("에러 - 스레드 생성 실패, 코드 %d\n", rc);
			return -1;
		}
	}

	for (t = 0; t < NUM_THREADS; t++) {
		pthread_join(threads[t], NULL);
	}

	printf("모든 스레드 실행 완료. \n");

	return 0;
}
