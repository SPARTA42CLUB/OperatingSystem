#include <semaphore.h>

int	main(void)
{
	sem_t	sem;

	// Create the semaphore and initialize it to 1
	sem_init(&sem, 0, 1); // warning: 'sem_init' is deprecated
	// https://stackoverflow.com/questions/27736618/why-are-sem-init-sem-getvalue-sem-destroy-deprecated-on-mac-os-x-and-w

	// acquire the semaphore
	sem_wait(&sem);

	// critical section

	// release the semaphore
	sem_post(&sem);
	return (0);
}
