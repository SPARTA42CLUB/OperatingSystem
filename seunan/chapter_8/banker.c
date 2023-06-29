#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NUM_THREADS 5
#define NUM_RESOURCES 3

int main(void)
{
	int		available[NUM_RESOURCES] = {3, 3, 2};
	int		max[NUM_THREADS][NUM_RESOURCES] =
	{
		{7, 5, 3}, // T0
		{3, 2, 2}, // T1
		{9, 0, 2}, // T2
		{2, 2, 2}, // T3
		{4, 3, 3}  // T4
	};
	int		allocation[NUM_THREADS][NUM_RESOURCES] =
	{
		{0, 1, 0}, // T0
		{2, 0, 0}, // T1
		{3, 0, 2}, // T2
		{2, 1, 1}, // T3
		{0, 0, 2}  // T4
	};
	int		need[NUM_THREADS][NUM_RESOURCES];
	bool	finish[NUM_THREADS] = { false };

	int		safe_sequence[NUM_THREADS];
	int		idx = 0;

	for (int i = 0; i < NUM_THREADS; i++) // need[i][j] = max[i][j] - allocation[i][j];
		for (int j = 0; j < NUM_RESOURCES; j++)
			need[i][j] = max[i][j] - allocation[i][j];

	for (int cnt = 0; cnt < NUM_THREADS; cnt++) // 최악의 경우 5회
	{
		for (int i = 0; i < NUM_THREADS; i++)
		{
			if (finish[i] == false) // && need[i] <= work(available)
			{
				bool flag = true; // 자원 중 하나라도 만족하지 않을 시 false
				for (int j = 0; j < NUM_RESOURCES; j++)
				{
					if (need[i][j] > available[j])
					{
						flag = false;
						break;
					}
				}
				if (flag == true)
				{
					safe_sequence[idx++] = i;
					for (int j = 0; j < NUM_RESOURCES; j++)
						available[j] += allocation[i][j]; // work += allocation
					finish[i] = true;
				}
			}
		}
	}

	bool isSafe = true; // 스레드 중 하나라도 finish[i] == false라면 false

	for (int i = 0; i < NUM_THREADS; i++)
	{
		if (finish[i] == false)
		{
			isSafe = false;
			printf("The following system is not safe");
			break;
		}
	}

	if (isSafe == true)
	{
		printf("Following is the SAFE Sequence\n");
		for (int i = 0; i < NUM_THREADS - 1; i++)
			printf("T%d -> ", safe_sequence[i]);
		printf("T%d", safe_sequence[NUM_THREADS - 1]);
	}
	return 0;
}
