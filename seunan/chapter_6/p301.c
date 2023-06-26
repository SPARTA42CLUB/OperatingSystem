#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct
{
	process	*next;
}	process;

typedef struct
{
	int	value;
	struct process *list;
} semaphore;

void	wait(semaphore *S)
{
	S->value--;
	if (S->value < 0)
	{
		// add this process to S->list
		// sleep();
	}
}

void	signal(semaphore *S)
{
	S->value++;
	if (S->value <= 0)
	{
		// remove a process P from S->list
		// wakeup(P);
	}
}

int	main(void)
{

	return (0);
}
