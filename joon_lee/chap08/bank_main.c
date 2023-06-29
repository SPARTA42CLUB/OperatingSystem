#include "bank.h"

int		THREAD, SOURCE;
int		AVAIL[101];
int		MAX[101][101];
int		ALLOC[101][101];
int		NEED[101][101];

void file_input(char *filename)
{
	FILE *file= fopen(filename, "r");
	fscanf(file, "%d %d\n", THREAD, SOURCE);
	for (int i = 0; i < THREAD; i++)
		fscanf(file,"%d", AVAIL[i]);
	for (int i = 0; i < THREAD; i++)
		for (int j = 0; j < SOURCE; j++)
			fscanf(file,"%d", MAX[i][j]);
	for (int i = 0; i < THREAD; i++)
		for (int j = 0; j < SOURCE; j++)
			fscanf(file,"%d", ALLOC[i][j]);
	for (int i = 0; i < THREAD; i++)
		for (int j = 0; j < SOURCE; j++)
			NEED[i][j] = MAX[i][j] - ALLOC[i][j];
}

bool banker_algo(void)
{
	bool	ret = false;
	bool	FINISH[THREAD];
	int 	WORK[SOURCE];

	//phase1
	for (int j = 0; j < SOURCE; j++)
			WORK[j] = AVAIL[j];
	for (int i = 0; i < THREAD; i++)
		FINISH[i] = false;
	//phase2
	for (int i = 0; i < THREAD; i++) {
		bool flag = true;
		for (int j = 0; j < SOURCE; j++) {
			if (!(FINISH[i] == false && NEED[i][j] <= WORK[j]))
				flag = false;
		}
		//phase3
		if (flag == true)
		{
			for (int j = 0; j < SOURCE; j++)
				WORK[j] += ALLOC[i][j];
			FINISH[i] = true;
			i = 0;
		}
	}
	//phase4
	for (int i = 0; i < THREAD; i++)
		if (FINISH[i] == false)
			return (false);
	return (true);
}


int main(int ac , char **av)
{
	if (ac != 2)
	{
		printf("invalid type of input\n");
		return (EXIT_FAILURE);
	}
	else {
		file_input(av[1]);
		bool ret = banker_algo();
		if (ret == true)
			printf("This system is safe\n");
		else
			printf("This system is unsafe\n");
		return (EXIT_SUCCESS);
	}
}
