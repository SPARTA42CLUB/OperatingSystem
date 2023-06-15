```c
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

```
비동기식 입출력을 이용한 예제입니다.

이 코드에서는 표준 입력(STDIN_FILENO)을 비차단(non-blocking) 모드로 설정하고, fgets 함수를 사용하여 입력을 받습니다.

그리고 fgets 함수가 NULL을 반환하는 동안 계속해서 "1"을 출력합니다. 사용자가 엔터를 입력하면 fgets 함수가 입력된 값을 읽고, 그 값을 출력한 뒤 프로그램이 종료됩니다.

- flags = fcntl(STDIN_FILENO, F_GETFL, 0);: STDIN_FILENO(표준 입력 파일 디스크립터)의 현재 플래그 값을 가져옵니다.
- fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);: STDIN_FILENO의 플래그 값을 가져와서 O_NONBLOCK 플래그를 추가하여 비차단 모드로 설정합니다.
- while (fgets(input, sizeof(input), stdin) == NULL): fgets 함수를 사용하여 입력을 받습니다. 이때 입력이 없으면(NULL을 반환하면) 계속해서 "1"을 출력합니다.
- 사용자가 엔터를 입력하면 fgets 함수가 입력된 값을 읽고, 이후에 코드가 진행됩니다.

```c
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char	input[256];

	printf("Enter a string: ");
	fgets(input, sizeof(input), stdin);
	while (fgets(input, sizeof(input), stdin) == NULL)
	{
		write(1, "1", 1);
	}
	printf("You entered: %s", input);
	return (0);
}

```
동기식 입출력을 사용한 예제입니다. 사용자의 입력을 받을 때까지 기다린 후에 입력된 값을 읽고 출력합니다.

- fgets(input, sizeof(input), stdin);: fgets 함수를 사용하여 사용자의 입력을 받습니다. 이때 사용자가 엔터를 입력하기 전까지 입력 대기 상태에 있습니다.
- while (fgets(input, sizeof(input), stdin) == NULL): fgets 함수를 사용하여 입력을 받습니다. 이때 입력이 없으면(NULL을 반환하면) 계속해서 "1"을 출력합니다.
- 사용자가 엔터를 입력하면 fgets 함수가 입력된 값을 읽고, 이후에 코드가 진행됩니다.


이렇게 두 코드의 차이는 입출력 함수를 호출하는 시점에서 비동기식과 동기식의 차이를 보여줍니다.

첫 번째 코드는 fgets 함수가 바로 반환되고 입력이 없을 때 "1"을 출력하며 대기하지 않습니다.

두 번째 코드는 fgets 함수가 사용자의 입력이 있을 때까지 대기하고, 입력을 받은 후에 출력합니다.
