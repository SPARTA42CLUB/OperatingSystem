#include <stdio.h>

// Number of processes
#define P 5
// Number of resources
#define R 3

// Function to find the need of each process
void calculateNeed(int need[P][R], int maxm[P][R], int allot[P][R])
{
    for (int i = 0 ; i < P ; i++)
        for (int j = 0 ; j < R ; j++)
            need[i][j] = maxm[i][j] - allot[i][j];
}

// Function to find the system is in safe state or not
int isSafe(int processes[], int avail[], int maxm[][R], int allot[][R])
{
    int need[P][R];

    calculateNeed(need, maxm, allot);

    int finish[P], safeSeq[P];
    for(int i=0; i<P; i++) finish[i] = 0;

    int work[R];
    for (int i = 0; i < R ; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < P)
    {
        int found = 0;
        for (int p = 0; p < P; p++)
        {
            if (finish[p] == 0)
            {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j]) break;

                if (j == R)
                {
                    for (int k = 0 ; k < R ; k++)
                        work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0)
        {
            printf("System is not in safe state");
            return 0;
        }
    }
    printf("System is in safe state.\nSafe sequence is: ");
    for (int i = 0; i < P ; i++)
        printf("%d ",safeSeq[i]);

    return 1;
}

// Resource request algorithm
int requestResource(int process_id, int request[], int processes[], int avail[], int maxm[][R], int allot[][R]) {
    for(int i=0; i<R; i++) {
        if(request[i] > (maxm[process_id][i] - allot[process_id][i])) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return -1;
        }

        if(request[i] > avail[i]) {
            printf("Process must wait, resources are not available.\n");
            return -1;
        }
    }

    // If resources are available, allocate them to process.
    for(int i=0; i<R; i++) {
        avail[i] -= request[i];
        allot[process_id][i] += request[i];
    }

    // Check if system is in safe state after resource allocation.
    if(isSafe(processes, avail, maxm, allot)) {
        printf("Resources allocated successfully.\n");
        return 0;
    } else {
        // If system is not in safe state, rollback.
        for(int i=0; i<R; i++) {
            avail[i] += request[i];
            allot[process_id][i] -= request[i];
        }
        printf("System is not in safe state. Request denied, rolled back.\n");
        return -1;
    }
}

int main()
{
    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {3, 3, 2};

    int maxm[][R] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};

    int allot[][R] = {{0, 1, 0},
                      {2, 0, 0},
                      {3, 0, 2},
                      {2, 1, 1},
                      {0, 0, 2}};

    isSafe(processes, avail, maxm, allot);

    int process_id = 1;
    int request[] = {1, 0, 2};

    requestResource(process_id, request, processes, avail, maxm, allot);

    return 0;
}
