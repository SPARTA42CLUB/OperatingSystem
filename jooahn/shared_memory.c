#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main()
{
    int     shm_id; // shared memory identifier
    char    *shm_ptr; // shared memory pointer
    pid_t   pid;

    // create shared memory
    shm_id =  shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id < 0)
    {
        perror("shmget failed\n");
        exit(1);
    }

    // 공유 메모리를 현재 프로세스의 주소 공간으로 첨부
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1)
    {
        perror("shmat error\n");
        exit(1);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork error\n");
        exit(1);
    }

    if (pid == 0)
    {
        printf("write shared memory at child process\n");
        sprintf(shm_ptr, "Hello, shared memory!");
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("read shared memory at parent process : %s\n", shm_ptr);

        // 공유 메모리 분리
        if (shmdt(shm_ptr) == -1)
        {
            perror("shmdt error\n");
            exit(1);
        }

        // 공유 메모리 삭제
        if (shmctl(shm_id, IPC_RMID, 0) == -1)
        {
            perror("shmctl error\n");
            exit(1);
        }
    }

    return 0;
}
