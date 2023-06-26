#include <semaphore.h>

int	main(void)
{
	sem_t	*sem;

	// Create the semaphore and initialize it to 1
	sem = sem_open("SEM", O_CREAT, 0666, 1);

	// acquire the semaphore
	sem_wait(sem);

	// critical section

	// release the semaphore
	sem_post(sem);
	return (0);
}
