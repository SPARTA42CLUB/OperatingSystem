#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define WRITE_END 1
#define READ_END 0

int	main(void)
{
	int		fd[2];
	pid_t	pid;
	int		ste;
	char	line[255];

	// 파이프를 생성한 후 디스크립터를 fd[0], fd[1]에 저장
	if (pipe(fd) == -1)
	{
		fprintf(stderr, "pipe error: %s\n", strerror(errno));
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		fprintf(stderr, "fork error: %s\n", strerror(errno));
		return (1);
	}
	else if (pid == 0) // 자식 프로세서가 처리하는 코드
	{
		// 표준 출력을 파이프의 쓰는 쪽으로 설정
		dup2(fd[1], WRITE_END);
		// 자식 프로세스는 파이프에서 읽지 않으므로 읽는 쪽을 닫는다.
		close(fd[0]);
		ste = execlp("ls", "ls", "-alR", NULL);
		if (ste == -1)
		{
			fprintf(stderr, "run error: %s\n", strerror(errno));
			return (1);
		}
	}
	// 부모 프로세스만 여기에 도달한다.
	// 표준 입력을 파이프의 읽는 쪽으로 리다이렉션한다.
	dup2(fd[0], READ_END);
	// 부모 프로세스는 파이프에 쓰지 않으므로 파이프의 쓰는 쪽을 닫는다.
	close(fd[1]);
	// 표준 입력이 파이프에 연결되어 있으므로 표준 입력에서 읽는다.
	// fd[0]을 사용해도 된다.
	while (fgets(line, sizeof(line), stdin) != 0)
		printf("%s", line);
	return (0);
}
