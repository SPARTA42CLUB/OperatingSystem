#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t   pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "fork failed\n");
        return 1;
    }
    // child process
    else if (pid == 0)
    {
        printf("Child process: PID = %d\n", getpid());

        // new process generated
        char *args[] = {"ls", "-al", NULL};
        execvp(args[0], args); // exec가 제대로 실행되면 새롭게 메모리가 적재돼, 이 밑으론 실행되지 않음

        fprintf(stderr, "exec failed\n");
        return 1;
    }
    // parent process
    else
    {
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        
        wait(NULL);
        printf("Child process terminated\n");
    }

    return 0;
}
