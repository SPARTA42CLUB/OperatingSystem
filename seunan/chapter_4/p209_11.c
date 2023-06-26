#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void	*worker(void *);

int	main(void)
{
	pthread_t	tid;
	static	__thread int threadID; // p211

	// create the thread
	pthread_create(&tid, 0, worker, NULL);

	//cancel for the thread to terminate
	pthread_join(tid, NULL);

	// p210
	while (1)
	{
		/* do some work for awhile */
		/* check if there is a cancellation request */
		pthread_testcancel();
	}

	return (0);
}
