#include <pthread.h>
#include <stdio.h>

#include <stdlib.h>

int sum; // 스레드에 의해 공유되는 데이터
void *runner(void *param); // threads call this func

int main(int argc, char *argv[]) {
	pthread_t tid; // thread identifier
	pthread_attr_t attr; // set of thread attributes

	// set the default attribute of the thread
	pthread_attr_init(&attr);

	// create the thread
	pthread_create(&tid, &attr, runner, argv[1]);

	// wait for the thread to exit
	pthread_join(tid, NULL);

	printf("sum = %d\n", sum);
}

// thread will execute in this func
void *runner(void *param)
{
	int i, upper = atoi(param);
	sum = 0;

	for (i = 1; i <= upper; i++)
		sum += i;

	pthread_exit(0);
}
