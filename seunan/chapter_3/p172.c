#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	// fork a children process
	fork();
	// fork another children process
	fork();
	// and fork another
	fork();
	return (0);
}
