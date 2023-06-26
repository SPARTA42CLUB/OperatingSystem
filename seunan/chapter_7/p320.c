#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10;

sem_t	mutex = 1;
sem_t	empty = N;
sem_t	full = 0;

int	main(void)
{
	// producer
	while (true)
	{
		// produce an item in next_produced
		sem_wait(empty);
		sem_wait(mutex);
		// add next_produced to the buffer
		signal(mutex);
		signal(full);
	}
	// consumer
	while (true)
	{
		sem_wait(full);
		sem_wait(mutex);
		// remove an item from buffer to next_consumed
		signal(mutex);
		signal(full);
		// consume the item in next_consumed
	}
	return (0);
}
