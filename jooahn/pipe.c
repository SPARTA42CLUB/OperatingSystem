#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define WRITE_END 1
#define READ_END 0

int main(void)
{
	int fd[2];

	if (pipe(fd) < 0)
	{
		perror("pipe error");
		return (EXIT_FAILURE);
	}
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[READ_END]);

		write(fd[WRITE_END], "hello", 6);
		close(fd[WRITE_END]);
		return (EXIT_SUCCESS);
	}
	else
	{
		char str[6];

		close(fd[WRITE_END]);
		read(fd[READ_END], str, 6);
		printf("received message : %s\n", str);
		return (EXIT_SUCCESS);
	}
}
