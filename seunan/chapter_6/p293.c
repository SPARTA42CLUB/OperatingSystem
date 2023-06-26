// test_and_set
// 상호 배제 조건은 만족시키나 한정된 대기 조건을 만족시키지 못함
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

bool	test_and_set(bool *target);

bool lock = 0;

int	main(void)
{
	do
	{
		while (test_and_set(&lock))
			; // do nothing

		// critical section
		// remainder section
	} while (true);

	return (0);
}

bool	test_and_set(bool *target)
{
	bool	rv = *target;
	*target = true;

	return (rv);
}
