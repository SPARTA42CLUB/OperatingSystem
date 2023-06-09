#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define  KEY_NUM     9527
#define  SHM_SIZE    1024

int main(int ac, char **av)
{
    int shmid;

    if(ac != 2)
    {
        perror("wrong number of argument!");
        exit(EXIT_FAILURE);
    }
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    char *to_send = (char *)shmat(shmid, (void *)0, 0);
    if (to_send == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();

    if (pid < 0) {
        // fork 실패 시 오류 메시지 출력
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        to_send = av[1];

    // if (shmdt(to_send) == -1) {
    //     perror("shmdt");
    //     exit(EXIT_FAILURE);
    // }
    }
    else
    {
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            printf("send complete.");
            exit(EXIT_FAILURE);
        }
    }
}