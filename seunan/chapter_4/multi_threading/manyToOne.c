#include <pthread.h>
#include <stdio.h>

void	*thread_function(void *arg) // thread가 실행하는 함수
{
	int	thread_id;

	thread_id = *((int *)arg);
	printf("Hello from thread %d\n", thread_id);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	thread;
	int			thread_id; // tid를 저장하기 위한 변수

	thread_id = 1;
	pthread_create(&thread, NULL, thread_function, &thread_id);
	pthread_join(thread, NULL);
	printf("Main thread exiting\n");
	return (0);
}
