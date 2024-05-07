#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	int	a[2];
	int	*p = a + 2;

	for (int i = 0; i < 2; i++)
		a[i] = i + 1;

	*p = 3;

	printf("&a[0] : %p\n", &a[0]);
	printf("&a[1] : %p\n", &a[1]);
	printf("&a[2] : %p\n", p);

	for (int i = 0; i < 3; i++)
		printf(" a[%d] : %d\n", i, *(a + 1 * i));

	remove("a.out");
	remove("tempCodeRunnerFile.c");

	return (0);
}
