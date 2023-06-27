// deadlock

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 10

void	*do_work_one(void *param);
void	*do_work_two(void *param);

pthread_mutex_t	first_mutex;
pthread_mutex_t	second_mutex;
int				cnt;

int	main(void)
{
	pthread_t	thread[2];

	pthread_mutex_init(&first_mutex, NULL);
	pthread_mutex_init(&second_mutex, NULL);

	pthread_create(&thread[0], NULL, do_work_one, NULL);
	pthread_create(&thread[1], NULL, do_work_two, NULL);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);

	pthread_mutex_destroy(&first_mutex);
	pthread_mutex_destroy(&second_mutex);

	printf("cnt = %d\n", cnt);
	return (0);
}

void	*do_work_one(void *param)
{
	(void) param;

	pthread_mutex_lock(&first_mutex);
	sleep(1);
	pthread_mutex_lock(&second_mutex);

	for (int i = 0; i < N; i++)
	{
		cnt++;
	}

	pthread_mutex_unlock(&second_mutex);
	pthread_mutex_unlock(&first_mutex);

	pthread_exit(0);
}
void	*do_work_two(void *param)
{
	(void) param;

	pthread_mutex_lock(&second_mutex);
	sleep(1);
	pthread_mutex_lock(&first_mutex);

	for (int i = 0; i < N; i++)
	{
		cnt++;
	}

	pthread_mutex_unlock(&first_mutex);
	pthread_mutex_unlock(&second_mutex);

	pthread_exit(0);
}
