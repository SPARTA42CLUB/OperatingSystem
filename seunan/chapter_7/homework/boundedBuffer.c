#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

// 공유 버퍼
int buffer[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t empty, full;

int in = 0, out = 0;

void insert_item(int item);
void remove_item(int *item);
void *producer(void *param);
void *consumer(void *param);

int main()
{
	int			numOfProducers = 5;
	int			numOfConsumers = 1;
	pthread_t	tid;

	// 뮤텍스 초기화
	pthread_mutex_init(&mutex, NULL);
	// 버퍼 사이즈로 empty 초기화
	sem_init(&empty, 0, BUFFER_SIZE);
	// full 초기화
	sem_init(&full, 0, 0);

	for (int i = 0; i < numOfProducers; i++)
		pthread_create(&tid, NULL, producer, NULL);

	for (int i = 0; i < numOfConsumers; i++)
		pthread_create(&tid, NULL, consumer, NULL);

	sleep(5);
	return 0;
}

void insert_item(int item)
{
	sem_wait(&empty); // wait
	pthread_mutex_lock(&mutex);

	// ciritcal section
	buffer[in] = item;
	in = (in + 1) % BUFFER_SIZE;
	printf("Producer: inserted $%d\n", item);

	pthread_mutex_unlock(&mutex);
	sem_post(&full); // signal
}

void remove_item(int *item)
{
	sem_wait(&full); // wait
	pthread_mutex_lock(&mutex);

	*item = buffer[out];
	out = (out + 1) % BUFFER_SIZE;
	printf("Consumer: removed $%d\n", *item);

	pthread_mutex_unlock(&mutex);
	sem_post(&empty); // signal
}

void *producer(void *param)
{
	int item;
	while (true)
	{
		// 0.1초 ~ 0.5초 사이를 슬립하게 해줌
		usleep((1+rand()%5)*100000);
		// 1000 ~ 2000까지의 수를 랜덤하게 만들어줌
		item = 1000 + rand()%1000;
		// 랜덤값을 버퍼에 집어 넣음
		insert_item(item); // critical section
	}
}

void *consumer(void *param)
{
	int item;
	while (true)
	{
		// 0.1초 ~ 0.5초 사이를 슬립하게 해줌
		usleep((1+rand()%5)*100000);
		// item을 하나 꺼내옴
		remove_item(&item);  // critical section
	}
}
