#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

void *count(void *arg);

sem_t	*unnamedSemaphore;
int		cnt;

int main(void)
{
	pthread_t	thread1,thread2;

	// Initialize the unnamed semaphore
	sem_init(unnamedSemaphore, 0, 1);


	pthread_create(&thread1, NULL, count, NULL);
	pthread_create(&thread2, NULL, count, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// Destroy the unnamed semaphore
	sem_destroy(unnamedSemaphore);

	printf("cnt = %d\n", cnt);

	return 0;
}

void *count(void *arg)
{
	(void) arg;

	// Wait on the unnamed semaphore
	sem_wait(unnamedSemaphore);

	//======== critical section =============
	for (int i = 0; i <1000000; i++)
		cnt++;
	//========= critical section ============

	// Release the unnamed semaphore
	sem_post(unnamedSemaphore);

	return (0);
}
