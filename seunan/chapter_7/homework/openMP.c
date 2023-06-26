// 안됨

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

void *count(void *arg);

int		cnt;

int main(void)
{
	pthread_t	thread1,thread2;

	pthread_create(&thread1, NULL, count, NULL);
	pthread_create(&thread2, NULL, count, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("cnt = %d\n", cnt);

	return 0;
}

void *count(void *arg)
{
	(void) arg;

	//======== critical section =============
	#pragma omp critical
	{
		for (int i = 0; i <1000000; i++)
			cnt++;
	}
	//========= critical section ============

	return (0);
}
