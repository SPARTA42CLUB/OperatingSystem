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
	while (true)
	{
		while (compare_and_swap(&lock, 0, 1) != 0)
			; // do nothing
		// critical section
		lock = 0;
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
