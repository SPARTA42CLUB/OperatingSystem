#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

#define N 5

void *count(void *arg);

sem_t	*namedSemaphore;
int		cnt;

int main(void)
{
	pthread_t	thread[N];

	// Create or open a named semaphore
	namedSemaphore = sem_open("/my_named_semaphore", O_CREAT, 0644, 1);
	if (namedSemaphore == SEM_FAILED)
	{
		perror("sem_open");
		return 1;
	}

	for (int i = 0; i < N; i++)
	{
		pthread_create(&thread[i], NULL, count, NULL);
	}

	for (int i = 0; i < N; i++)
	{
		pthread_join(thread[i], NULL);
	}

	// Close and unlink the named semaphore
	sem_close(namedSemaphore);
	sem_unlink("/my_named_semaphore");

	printf("cnt = %d\n", cnt);

	return 0;
}

void *count(void *arg)
{
	(void) arg;

	// Wait on the named semaphore
	sem_wait(namedSemaphore);

	//======== critical section =============
	for (int i = 0; i <1000000; i++)
		cnt++;
	//========= critical section ============

	// Release the named semaphore
	sem_post(namedSemaphore);

	return (0);
}
