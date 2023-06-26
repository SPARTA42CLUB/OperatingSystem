#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex;
int cnt=0;

void *count(void *arg);

int main()
{
	pthread_t thread1,thread2;

	pthread_mutex_init(&mutex,NULL);

	pthread_create(&thread1, NULL, count, (void *)"thread1");
	pthread_create(&thread2, NULL, count, (void *)"thread2");


	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&mutex);

	printf("cnt: %d\n",cnt);
}

void *count(void *arg){
	int i;
	(void) arg;

	pthread_mutex_lock(&mutex);

	//======== critical section =============
	for (i = 0; i <1000000; i++)
		cnt++;
	//========= critical section ============
	pthread_mutex_unlock(&mutex);
	return (0);
}
