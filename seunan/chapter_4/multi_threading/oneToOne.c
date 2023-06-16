#include <pthread.h>
#include <stdio.h>

void	*thread_function(void *arg)
{
	int	thread_id;

	thread_id = *((int *)arg);
	printf("Hello from thread %d\n", thread_id);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	threads[3];
	int			thread_ids[3] = {1, 2, 3};

	for (int i = 0; i < 3; i++)
	{
		pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
		pthread_join(threads[i], NULL);
	}
	printf("Main thread exiting\n");
	return (0);
}
