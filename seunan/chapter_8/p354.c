#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 10

void *do_work_one(void *param);
void *do_work_two(void *param);

pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;
int cnt;

int main(void)
{
	pthread_t thread[2];

	pthread_mutex_init(&first_mutex, NULL);
	pthread_mutex_init(&second_mutex, NULL);

	pthread_create(&thread[0], NULL, do_work_one, NULL);
	pthread_create(&thread[1], NULL, do_work_two, NULL);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);

	pthread_mutex_destroy(&first_mutex);
	pthread_mutex_destroy(&second_mutex);

	printf("cnt = %d\n", cnt);
	return 0;
}

void *do_work_one(void *param)
{
	(void) param;

	int done = 0;

	while (!done)
	{
		pthread_mutex_lock(&first_mutex);
		if (pthread_mutex_trylock(&second_mutex))
		{
			for (int i = 0; i < N; i++)
			{
				cnt++;
			}
			pthread_mutex_unlock(&second_mutex);
			pthread_mutex_unlock(&first_mutex);
			done = 1;
		}
		else
		{
			pthread_mutex_unlock(&first_mutex);
			sleep(2);  // 잠시 대기
		}
	}

	pthread_exit(0);
}

void *do_work_two(void *param)
{
	(void) param;

	int done = 0;

	while (!done)
	{
		pthread_mutex_lock(&second_mutex);
		if (pthread_mutex_trylock(&first_mutex))
		{
			for (int i = 0; i < N; i++)
			{
				cnt++;
			}
			pthread_mutex_unlock(&first_mutex);
			pthread_mutex_unlock(&second_mutex);
			done = 1;
		}
		else
		{
			pthread_mutex_unlock(&second_mutex);
			sleep(2);  // 잠시 대기
		}
	}

	pthread_exit(0);
}
