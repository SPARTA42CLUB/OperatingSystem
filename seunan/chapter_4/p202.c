// #include <omp.h>
// gcc -fopenmp 플래그를 사용해서 OpenMP인식 + 활성화
#include <stdio.h>

#define N 10

int	main(void)
{
	// sequential code
	#pragma omp parallel // system의 core 개수만큼 thread 생성
	{
		printf("I am a parallel region.\n");
	}

	int	a[N], b[N], c[N];
	for (int i = 0; i < N; i++)
	{
		a[i] = i;
		b[i] = i + 1;
	}

	#pragma omp parallel for // for문 안의 연산을 directive에 따라 생성된 threads에게 분배
	for (int i = 0; i < N; i++)
	{
		c[i] = a[i] + b[i];
	}

	for (int i = 0; i < N; i++)
	{
		printf("%d ", c[i]);
	}

	return (0);
}
