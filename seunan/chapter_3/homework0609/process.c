#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid; // 프로세스 id를 저장할 변수
	int		status; // 자식 프로세스의 종료 상태를 저장할 변수

	pid = fork(); // 새로운 프로세스 생성
	if (pid < 0) // fork()가 음수 반환 시 오류
	{
		perror("fork error");
		exit(1);
	}
	else if (pid == 0) // fork()가 0 반환 시 현재 코드가 자식 프로세스에서 실행 중을 의미
	{
		// 자식 프로세스인 경우
		// 새로운 프로그램 실행
		execl("/bin/ls", "ls", "-l", NULL); // execl()을 이용하여 "ls -l" 실행
		// exec 함수가 실행되면 이후의 코드는 실행되지 않음
		perror("execl error");
		exit(1);
	}
	else
	{
		// 부모 프로세스인 경우
		wait(&status); // 자식 프로세스의 종료를 기다림
		if (WIFEXITED(status)) // WIFEXITED() 매크로는 자식 프로세스가 정상적으로 종료되었는 지 확인, 조건이 참일 경우 자식 프로세스 종료
		{
			printf("Child process exited with status: %d\n",
					WEXITSTATUS(status));
		}
		else // 참이 아니라면 비정상 종료를 의미
		{
			printf("Child process terminated abnormally\n");
		}
	}
	return (0);
}
// 이 코드는 fork()를 사용하여 새로운 자식 프로세스를 생성하고, 자식 프로세스는 execl()을 사용하여 "ls -l" 명령을 실행합니다. 부모 프로세스는 자식 프로세스의 완료를 기다리고, 자식 프로세스의 종료 상태를 출력합니다.
