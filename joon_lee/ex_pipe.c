#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define WRITE 1
#define READ 0

int main(void) {
	int fd[2];



	if (pipe(fd) == -1) {
		perror("pipe");
		return (EXIT_FAILURE);
	}
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0) { //child
		close(fd[READ]);

		write(fd[WRITE], "hello", 6);
		close(fd[WRITE]);
		return (EXIT_SUCCESS);
	}
	else { //parent
		char	str[6];

		close(fd[WRITE]);
		read(fd[READ], str, 6);
		printf("received message : %s\n", str);
		return (EXIT_SUCCESS);
	}
}
