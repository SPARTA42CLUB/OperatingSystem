#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char	input[256];
	int		flags;

	printf("Enter a string: ");
	fflush(stdout);
	// 파일 디스크립터(STDIN_FILENO)를 비차단(non-blocking) 모드로 설정
	flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
	while (fgets(input, sizeof(input), stdin) == NULL)
	{
		write(1, "1", 1);
	}
	printf("You entered: %s", input);
	return (0);
}
