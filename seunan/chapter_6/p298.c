#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

bool	available;

void	acquire(void)
{
	while (!available)
		; // busy wait
	available = false;
}

void	release(void)
{
	available = true;
}

int	main(void)
{
	while (true)
	{
		acquire();
			// critical section
		release();
			// remainder section
	}

	return (0);
}
