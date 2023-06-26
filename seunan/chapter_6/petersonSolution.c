#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define NUM_THREADS 2

int		turn;
bool	flag[NUM_THREADS];
int		critical_section_variable;

void* thread_function(void *thread_id) {
	int tid = *(int *) thread_id;
	int other = 1 - tid;

	flag[tid] = true;
	turn = other;

	while (flag[other] == true && turn == other)
		/* printf("기다리는 스레드%d\n", tid) */; // 상대 스레드가 일할 때까지 기다림 -> entry section

	// Critical Section 시작
	printf("스레드 %d이(가) Critical Section에 진입합니다.\n", tid);
	for (int i = 0; i < 10000; i++)
		critical_section_variable++;
	printf("스레드 %d이(가) Critical Section에서 작업을 수행합니다. 변수 값: %d\n", tid, critical_section_variable);
	printf("스레드 %d이(가) Critical Section을 빠져나옵니다.\n", tid);
	// Critical Section 종료

	flag[tid] = false; // exit section
	return (0);
}

int main() {
	pthread_t threads[NUM_THREADS];
	int thread_ids[NUM_THREADS];

	// 초기화
	turn = 0;
	flag[0] = false;
	flag[1] = false;
	critical_section_variable = 0;

	// 스레드 생성 및 실행
	for (int i = 0; i < NUM_THREADS; i++) {
		thread_ids[i] = i; // create threads T0, T1
		pthread_create(&threads[i], NULL, thread_function, (void *)&thread_ids[i]);
		// 운영 체제 스케줄러의 동작, 스레드의 우선순위, 다른 프로세스나 스레드들의 작업량 등의 영향으로 스레드의 순서는 매번 다름
	}

	// 스레드 종료 대기
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
		// 생성된 스레드가 종료될 때까지 현재 스레드(주로 메인 스레드) 대기
	}

	remove("a.out");
	remove("tempCodeRunnerFile.c");
	return 0;
}
