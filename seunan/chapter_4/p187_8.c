#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10 // p188 조인할 스레드의 수

int		sum; // this data is shared by the threads
void	*runner(void *param); // threads call this function

int	main(int ac, char *av[])
{
	(void) ac;
	pthread_t		tid; // the thread identifier
	pthread_attr_t	attr; // set of thread attributes

	// set the default attributes of the thread
	pthread_attr_init(&attr);
	// creat the thread
	pthread_create(&tid, &attr, runner, av[1]);
	// wait for the thread to exit
	pthread_join(tid, NULL);

	printf("sum = %d\n", sum);

	// p188
	// an array of threads to be joined upon
	pthread_t	workers[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(workers[i], NULL);

	return (0);
}

// the thread will execute in this function
void	*runner(void *param)
{
	int i, upper = atoi(param);
	sum = 0;

	for (i = 1; i <= upper; i++)
		sum += i;
	pthread_exit(0);
}
