#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define THREAD_NUM 100

pthread_mutex_t lock;

void *print_number(void *t)
{
	pthread_mutex_lock(&lock);
	for (int i = 0; i < 5; i++)
		printf("%d\n", i+1);
	pthread_mutex_unlock(&lock);
	return 0;
}

int main(void)
{
	pthread_t	thread[THREAD_NUM];

	pthread_mutex_init(&lock , 0);
	for (int i = 0; i < THREAD_NUM; i++)
		pthread_create(&thread[i], 0, print_number, 0);
	for (int i = 0; i < THREAD_NUM; i++)
		pthread_join(thread[i], 0);
}
