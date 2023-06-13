#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024 // 공유 메모리 크기

int	main(void)
{
	key_t	key; /// 공유 메모리의 키를 저장할 변수
	int		shm_id; // 공유 메모리 식별자를 저장할 변수
	char	*shm_addr; // 공유 메모리에 연결된 메모리 주소를 저장할 변수
	char	message[SHM_SIZE];

	// 공유 메모리 키 생성
	key = ftok(".", 'x'); // ftok() 함수는 현재 작업 디렉토리와 키 식별자를 기반으로 고유한 키 값을 생성
	if (key == -1) // 키 생성 실패 시 -1 반환
	{
		perror("ftok error");
		exit(1);
	}
	// 공유 메모리 생성
	shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666); // shmget() 함수는 공유 메모리 식별자를 반환
	// key는 키 값, SHM_SIZE는 생성 또는 연결할 공유 메모리의 크기, 0666은 권한
	if (shm_id == -1) // 공유 메모리 생성 또는 연결에 실패한 경우 -1이 반환
	{
		perror("shmget error");
		exit(1);
	}
	// 공유 메모리에 연결
	shm_addr = shmat(shm_id, (void *)0, 0); // shmat() 함수는 공유 메모리에 연결된 메모리 주소를 반환
	// shm_id는 공유 메모리 식별자, (void *)0은 원하는 메모리 주소 (0은 시스템이 알아서 선택하도록 함)
	if (shm_addr == (char *)(-1)) // shmat() 함수 호출에 실패한 경우 (char *)(-1)이 반환
	{
		perror("shmat error");
		exit(1);
	}
	// 데이터 입력 받기
	printf("Enter a message: ");
	fgets(message, SHM_SIZE, stdin);
	// 공유 메모리에 데이터 쓰기
	strncpy(shm_addr, message, SHM_SIZE);
	// 공유 메모리에서 연결 해제
	if (shmdt(shm_addr) == -1) // // shmdt() 함수를 사용하여 공유 메모리와의 연결을 해제
	{
		perror("shmdt error");
		exit(1);
	}
	return (0);
}
