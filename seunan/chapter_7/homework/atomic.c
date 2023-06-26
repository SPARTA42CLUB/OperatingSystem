#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>

atomic_int	cnt;
int			value;

void *count(void *arg);

int	main(void)
{
	pthread_t thread1,thread2;

	pthread_create(&thread1, NULL, count, NULL);
	pthread_create(&thread2, NULL, count, NULL);


	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("cnt: %d\n",cnt);

	remove("a.out");
	remove("tempCodeRunnerFile.c");
	return (0);
}

void *count(void *arg)
{
	(void) arg;

	//======== critical section =============
	for (int i = 0; i <1000000; i++)
		cnt++;
	//========= critical section ============
	return (0);
}
