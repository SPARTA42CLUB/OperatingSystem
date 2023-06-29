#include <stdio.h>
#include <stdbool.h>

#define MAX_RESOURCES 100
#define MAX_CUSTOMERS 100

int available[MAX_RESOURCES];
int maximum[MAX_CUSTOMERS][MAX_RESOURCES];
int allocate[MAX_CUSTOMERS][MAX_RESOURCES];
int need[MAX_CUSTOMERS][MAX_RESOURCES];
bool finished[MAX_CUSTOMERS];

void	inputData(int numResources, int numCustomers)
{
	printf("Enter the number of available resources:\n");
	for (int i = 0; i < numResources; i++)
		scanf("%d", &available[i]);

	printf("Enter the maximum needed resources for each customer:\n");
	for (int i = 0; i < numCustomers; i++)
	{
		printf("Customer %d: ", i + 1);
		for (int j = 0; j < numResources; j++)
			scanf("%d", &maximum[i][j]);
		finished[i] = false;
	}

	printf("Enter the current allocation of resources for each customer:\n");
	for (int i = 0; i < numCustomers; i++)
	{
		printf("Customer %d: ", i + 1);
		for (int j = 0; j < numResources; j++)
		{
			scanf("%d", &allocate[i][j]);
			need[i][j] = maximum[i][j] - allocate[i][j];
		}
	}
}

bool	isSafeState(int numResources, int numCustomers)
{
	int work[MAX_RESOURCES];
	bool canFinish = true;

	for (int i = 0; i < numResources; i++) {
		work[i] = available[i];
	}

	while (true)
	{
		bool found = false;

		for (int i = 0; i < numCustomers; i++)
		{
			if (!finished[i]) {
				bool hasEnoughResources = true;

				for (int j = 0; j < numResources; j++) {
					if (need[i][j] > work[j]) {
						hasEnoughResources = false;
						break;
					}
				}


				if (hasEnoughResources)
				{
					for (int j = 0; j < numResources; j++) {
						work[j] += allocate[i][j];
					}
					finished[i] = true;
					found = true;
					break;
				}
			}
		}
		if (!found) {
			break;
		}
	}

	for (int i = 0; i < numCustomers; i++) {
		if (!finished[i]) {
			canFinish = false;
			break;
		}
	}
	return canFinish;
}

int main(void)
{
	int numResources, numCustomers;

	printf("Enter the number of resource types: ");
	scanf("%d", &numResources);

	printf("Enter the number of customers: ");
	scanf("%d", &numCustomers);

	inputData(numResources, numCustomers);

	if (isSafeState(numResources, numCustomers))
		printf("The system is in a safe state. All customer requests can be satisfied.\n");
	else
		printf("The system is in a deadlock state. The requests cannot be satisfied.\n");

	return (0);
}
