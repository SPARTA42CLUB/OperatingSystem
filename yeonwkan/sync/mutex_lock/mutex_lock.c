#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int cnt;
pthread_mutex_t mutex;

void *count(void *arg){
	int i;
	char *name = (char *)arg;
	 
	pthread_mutex_lock(&mutex);
	//=============== critical section ==================
	cnt = 0 ;
	for (i = 0; i < 10; i++){
		printf("%s cnt: %d\n", name, cnt);
		cnt++;
		usleep(1);
	}
	//=============== critical section ==================
	pthread_mutex_unlock(&mutex);
}

int main(void)
{
	pthread_t thread1, thread2;

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&thread1, NULL, count, (void *)"thread1");	
	pthread_create(&thread2, NULL, count, (void *)"thread2");	

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&mutex);
	return (0);
}