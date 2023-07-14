#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char *ptr = malloc(sizeof(char) * 1024);
	for (int i = 0; i < 1024; i++)
		printf("%d\n", ptr[i]);
	return (0);
}
