// Banker's Algorithm
#include <stdio.h>
#include <stdbool.h>

int main()
{
    // P0, P1, P2, P3, P4 are the Process names here

    int n, m, i, j, k;
    n = 5;                         // Number of processes
    m = 3;                         // Number of resources
    int alloc[5][3] = {{0, 1, 0},  // P0 // Allocation Matrix
                       {2, 0, 0},  // P1
                       {3, 0, 2},  // P2
                       {2, 1, 1},  // P3
                       {0, 0, 2}}; // P4

    int max[5][3] = {{7, 5, 3},  // P0 // MAX Matrix
                     {3, 2, 2},  // P1
                     {9, 0, 2},  // P2
                     {2, 2, 2},  // P3
                     {4, 3, 3}}; // P4

    int avail[3] = {3, 3, 2}; // Available Resources

    // 초기화
    int work[m];
    for (i = 0; i < m; i++)
        work[i] = avail[i];

    bool finish[n];
    for (k = 0; k < n; k++)
        finish[k] = false;

    int need[n][m];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    int safe_cycle[n];
    int safe_index = 0;
    for (i = 0; i < n; i++)
    {
        bool flag = false; // 프로세스별로 flag 초기화
        if (finish[i] == false)
        {
            for (j = 0; j < m; j++)
            {
                if (need[i][j] > work[j])
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                for (int t = 0; t < m; t++)
                    work[t] += alloc[i][t];
                finish[i] = true;
                safe_cycle[safe_index++] = i;
                i = -1; // 처음부터 다시 검사
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        if (finish[i] == false)
        {
            printf("not safe\n");
            return 0;
        }
    }
    printf("Safe sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safe_cycle[i]);
    printf("\n");
    return 0;
}
