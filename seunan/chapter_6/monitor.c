#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 5

pthread_mutex_t mutex;
pthread_cond_t buffer_full;
pthread_cond_t buffer_empty;
int buffer[BUFFER_SIZE];
int count = 0;

void produce(int item) {
	pthread_mutex_lock(&mutex);

	while (count == BUFFER_SIZE) {
		pthread_cond_wait(&buffer_empty, &mutex);
	}

	buffer[count] = item;
	count++;

	pthread_cond_signal(&buffer_full);
	pthread_mutex_unlock(&mutex);
}

int consume() {
	pthread_mutex_lock(&mutex);

	while (count == 0) {
		pthread_cond_wait(&buffer_full, &mutex);
	}

	int item = buffer[count - 1];
	count--;

	pthread_cond_signal(&buffer_empty);
	pthread_mutex_unlock(&mutex);

	return item;
}

void* producer(void* arg)
{
	(void) arg;
	for (int i = 1; i <= 10; i++) {
		produce(i);
		printf("Produced: %d\n", i);
		usleep(rand() % 1000000);  // 임의의 대기 시간 추가
	}

	pthread_exit(NULL);
}

void* consumer(void* arg)
{
	(void) arg;
	for (int i = 1; i <= 10; i++) {
		int item = consume();
		printf("Consumed: %d\n", item);
		usleep(rand() % 1000000);  // 임의의 대기 시간 추가
	}

	pthread_exit(NULL);
}

int main() {
	pthread_t producer_thread, consumer_thread;

	// 뮤텍스와 조건변수 초기화
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&buffer_full, NULL);
	pthread_cond_init(&buffer_empty, NULL);

	// 생산자 스레드 생성 및 실행
	pthread_create(&producer_thread, NULL, producer, NULL);

	// 소비자 스레드 생성 및 실행
	pthread_create(&consumer_thread, NULL, consumer, NULL);

	// 생산자 스레드 종료 대기
	pthread_join(producer_thread, NULL);

	// 소비자 스레드 종료 대기
	pthread_join(consumer_thread, NULL);

	// 뮤텍스와 조건변수 해제
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&buffer_full);
	pthread_cond_destroy(&buffer_empty);

	return 0;
}
