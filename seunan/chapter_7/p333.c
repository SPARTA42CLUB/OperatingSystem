#include <pthread.h>

int	a, b;

int main()
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond_var;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_var, NULL);

	pthread_mutex_lock(&mutex);
	while (a != b)
		pthread_cond_wait(&cond_var, &mutex);

	pthread_mutex_unlock(&mutex);

	return 0;
}
