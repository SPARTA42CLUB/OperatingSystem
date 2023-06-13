#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int pid;
	execl("/bin/ls", "ls", "-l", 0);
	printf("exec change process, so this message don't show");
}