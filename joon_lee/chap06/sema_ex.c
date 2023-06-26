#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 100

sem_t lock;

void *print_number(void *t)
{
	sem_wait(&lock);
	for (int i = 0; i < 5; i++)
		printf("%d\n", i+1);
	sem_post(&lock);
	return 0;
}

int main(void)
{
	pthread_t	thread[THREAD_NUM];

	sem_init(&lock, 0, 1);
	for (int i = 0; i < THREAD_NUM; i++)
	{
		pthread_create(&thread[i], 0, print_number, 0);
		usleep(100);
	}
	for (int i = 0; i < THREAD_NUM; i++)
		pthread_join(thread[i], 0);
	sem_destroy(&lock);
}
