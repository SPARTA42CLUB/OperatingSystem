#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main()
{
	int fd1[2], fd2[2];
	pid_t	pid;
	char	buf[257];
	int		len, status;

	if (pipe(fd1) == -1) {
		perror("pipe");
		exit(1);
	}

	if (pipe(fd2) == -1) {
		perror("pipe");
		exit(1);
	}

	switch (pid = fork()) {
		case -1 :
			perror("fork");
			exit(1);
			break;
		case 0 :
			close(fd1[WRITE_END]);
			close(fd2[READ_END]);
			len = read(fd1[READ_END], buf, 256);
			write(1, "Child Process:", 15);
			write(1, buf, len);

			strcpy(buf, "Good\n");
			write(fd2[WRITE_END], buf, strlen(buf));
			close(fd1[READ_END]);
			close(fd2[WRITE_END]);
			break;
		default :
			close(fd1[READ_END]);
			close(fd2[WRITE_END]);
			write(fd1[WRITE_END], "Hello\n", 7);

			len = read(fd2[READ_END], buf, 256);
			write(1, "Parent Process:", 16);
			write(1, buf, len);
			waitpid(pid, &status, 0);
			close(fd1[WRITE_END]);
			close(fd2[READ_END]);
			break;
		}
}
