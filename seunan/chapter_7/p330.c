#include <pthread.h>

int	main(void)
{
	pthread_mutex_t	mutex;

	// create and initialize the mutex lock
	pthread_mutex_init(&mutex, NULL);

	// acquire the mutex lock
	pthread_mutex_lock(&mutex);

	// critical section

	// release the mutex lock
	pthread_mutex_unlock(&mutex);
	return (0);
}
