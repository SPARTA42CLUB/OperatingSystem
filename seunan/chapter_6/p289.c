#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int	main(void)
{
	int		turn;
	bool	flag[2];
	int		i = 0, j = 1;

	while (true)
	{
		flag[i] = true;
		turn = j;
		while (flag[j] && turn == j)
			;
		// critical section
		flag[i] = false;
		// remainder section
	}
	return (0);
}
