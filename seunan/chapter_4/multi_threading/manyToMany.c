#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 3

void	*thread_function(void *arg)
{
	int	thread_id;

	thread_id = *((int *)arg);
	printf("Hello from thread %d\n", thread_id);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	threads[NUM_THREADS];
	int			thread_ids[NUM_THREADS] = {1, 2, 3};

	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
	}
	/* for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	} */
	printf("Main thread exiting\n");
	return (0);
}
