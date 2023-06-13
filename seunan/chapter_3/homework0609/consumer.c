#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024 // 공유 메모리 크기

int	main(void)
{
	key_t	key;
	int		shm_id;
	char	*shm_addr;

	// 공유 메모리 키 생성
	key = ftok(".", 'x');
	if (key == -1)
	{
		perror("ftok error");
		exit(1);
	}
	// 공유 메모리에 연결
	shm_id = shmget(key, SHM_SIZE, 0666);
	if (shm_id == -1)
	{
		perror("shmget error");
		exit(1);
	}
	// 공유 메모리에 연결
	shm_addr = shmat(shm_id, (void *)0, 0);
	if (shm_addr == (char *)(-1))
	{
		perror("shmat error");
		exit(1);
	}
	// 공유 메모리에서 데이터 읽기
	printf("Data read from shared memory: %s\n", shm_addr);
	// 공유 메모리에서 연결 해제
	if (shmdt(shm_addr) == -1) // shmdt() 함수를 사용하여 공유 메모리와의 연결을 해제
	{
		perror("shmdt error");
		exit(1);
	}
	return (0);
}
