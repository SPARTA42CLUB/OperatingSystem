#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	int		status;

	// 새로운 프로세스 생성
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if (pid == 0)
	{
		// 자식 프로세스인 경우
		// 새로운 프로그램 실행
		execl("/bin/ls", "ls", "-l", NULL);
		// exec 함수가 실행되면 이후의 코드는 실행되지 않음
		perror("execl error");
		exit(1);
	}
	else
	{
		// 부모 프로세스인 경우
		// 자식 프로세스의 종료를 기다림
		wait(&status);
		if (WIFEXITED(status))
		{
			printf("Child process exited with status: %d\n",
					WEXITSTATUS(status));
		}
		else
		{
			printf("Child process terminated abnormally\n");
		}
	}
	return (0);
}
