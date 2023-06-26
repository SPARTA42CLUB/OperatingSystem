#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <stdatomic.h>

sem_t	chopstick[5] = { 1 };

int	main(void)
{
	int	i;
	while (true)
	{
		wait(chopstick[i]);
		wait(chopstick[(i + 1) % 5]);
		// eat for a while
		signal(chopstick[i]);
		signal(chopstick[(i + 1) % 5]);
		// think for awhile
	}

	return (0);
}
