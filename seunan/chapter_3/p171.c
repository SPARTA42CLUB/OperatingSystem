#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int	value = 5;

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0) // children process
	{
		value += 15;
		return (0);
	}
	else if (pid > 0) // parent process
	{
		wait(NULL);
		printf("PARENT: value = %d\n", value);
		return (0);
	}
}
