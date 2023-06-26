#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

void	wait(int S)
{
	while (S <= 0)
		; // busy wait
	S--;
}

void	signal(int S)
{
	S++;
}

int	main(void)
{

	return (0);
}
