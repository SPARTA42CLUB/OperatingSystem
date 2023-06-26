#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t s;
int count;

void *incrCount(void *arg){
	for (int i = 0; i < 100000; i++){
		sem_wait(&s);
		count++;
		sem_post(&s);
	}
}
void *decrCount(void *arg){
	for (int i = 0; i < 100000; i++){
		sem_wait(&s);
		count--;
		sem_post(&s);
	}
}
int main(void)
{
	sem_init(&s, 0, 1);

	pthread_t thread[20];
	int t[2] = {0, 1};

	int pid;

	for(int i = 0; i < 4; i=i+2){
		pid += pthread_create(&thread[i], NULL, incrCount, &t[0]);
		pid += pthread_create(&thread[i+1], NULL, decrCount, &t[1]);
	}

	if (pid < 0){
		printf("creating threads failed\n");
		return -1;
	}
	for (int i = 0; i < 20; i++){
		pthread_join(thread[i], NULL);
	}

	printf("final value of count = %d \n", count);
	sem_destroy(&s);
	return (0);
}