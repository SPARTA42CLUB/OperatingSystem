// compare_and_swap
// 임계구역 요구 조건을 모두 만족시킴
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define N 10

int	compare_and_swap(int *value, int expected, int new_value);

bool	waiting[N] = { false };
int		lock = 0;

int	main(void)
{
	int	key, i, j;

	while (true)
	{
		waiting[i] = true;
		key = 1;
		while (waiting[i] && key == 1)
			key = compare_and_swap(&lock, 0, 1);
		waiting[i] = false;

		// critical section

		j = (i + 1) % N;
		while (j != 1 && !waiting[i])
			j = (j + 1) % N;
		if (j == i)
			lock = 0;
		else
			waiting[j] = false;

		// remainder section
	}

	return (0);
}

int	compare_and_swap(int *value, int expected, int new_value)
{
	int	tmp = *value;
	if (*value == expected)
		*value = new_value;
	return (tmp);
}
