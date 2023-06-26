#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

sem_t	rw_mutex = 1;
sem_t	mutex = 1;
int		read_cnt = 0;

int	main(void)
{
	// writer
	while (true)
	{
		wait(rw_mutex);
		// writing is performed
		signal(rw_mutex);
	}

	// reader
	while (true)
	{
		wait(mutex);
		read_cnt++;
		if (read_cnt == 1)
			wait(rw_mutex);
		signal(mutex);
		// reading is performed
		wait(mutex);
		read_cnt--;
		if (read_cnt == 0)
			signal(rw_mutex);
		signal(mutex);
	}


	return (0);
}
