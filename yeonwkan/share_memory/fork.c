#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		printf("if pid = 0 , this is child pid value is = %d\n", pid);
	else if (pid > 0)
		printf("if pid > 0 , this is parent. pid vlaue is child's pid. pid =  %d\n", pid);
	else
		printf("fork failed\n");
}