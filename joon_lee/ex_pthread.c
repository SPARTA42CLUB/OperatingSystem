#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*get_goal(void * param)
{
	printf("#");
	return (0);
}


int main(int ac, char **argv)
{
	pthread_t	tid[5];
	pthread_attr_t	attr;

	pthread_attr_init(&attr);
	for (int i = 0; i < 5; i++)
		pthread_create(&tid[i], &attr, get_goal, argv[1]);
	pthread_join(tid[0], 0);
}
