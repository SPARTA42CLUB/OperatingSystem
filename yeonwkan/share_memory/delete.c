#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY_NUM     9527
#define MEM_SIZE    1024

int main()
{
	int shm_id;	
	void *shm_addr;
	int flag;
	shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT|0666);
	shm_addr = shmat( shm_id, ( void *)0, 0);
	printf("%p\n", shm_addr);
	flag = shmctl();
	if (!flag)
		printf("shmdt success\n");
	else
		printf("shmdt fail\n");
}