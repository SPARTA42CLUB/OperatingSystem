#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char	input[256];

	printf("Enter a string: ");
	fgets(input, sizeof(input), stdin);
	while (fgets(input, sizeof(input), stdin) == NULL)
	{
		write(1, "1", 1);
	}
	printf("You entered: %s", input);
	return (0);
}
