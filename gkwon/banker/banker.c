// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <time.h>

// #define NUM_RESOURCES 3

// bool is_safe_state(int available[], int max[][NUM_RESOURCES], int allocation[][NUM_RESOURCES], int need[][NUM_RESOURCES], int num_processes) {
//     bool finish[num_processes];
//     int work[NUM_RESOURCES];
//     int i, j;

//     // 초기화
//     for (i = 0; i < num_processes; i++)
//         finish[i] = false;

//     for (i = 0; i < NUM_RESOURCES; i++)
//         work[i] = available[i];

//     // 안전성 검사
//     int count = 0;
//     while (count < num_processes) {
//         bool found = false;
//         for (i = 0; i < num_processes; i++) {
//             if (!finish[i]) {
//                 bool can_allocate = true;
//                 for (j = 0; j < NUM_RESOURCES; j++) {
//                     if (need[i][j] > work[j]) {
//                         can_allocate = false;
//                         break;
//                     }
//                 }
//                 if (can_allocate) {
//                     for (j = 0; j < NUM_RESOURCES; j++)
//                         work[j] += allocation[i][j];

//                     finish[i] = true;
//                     found = true;
//                     count++;
//                     break;
//                 }
//             }
//         }
//         if (!found)
//             break;
//     }

//     // 안전 상태 여부 반환
//     if (count == num_processes)
//         return true;
//     else
//         return false;
// }

// int main() {
//     // 랜덤 값을 위한 시드 설정
//     srand(time(NULL));

//     int num_processes = 5;  // 프로세스 수

//     int available[NUM_RESOURCES];
//     int max[num_processes][NUM_RESOURCES];
//     int allocation[num_processes][NUM_RESOURCES];
//     int need[num_processes][NUM_RESOURCES];
//     int i, j;

//     // available 배열 초기화
//     for (i = 0; i < NUM_RESOURCES; i++)
//     {
//         available[i] = rand() % 10;
//         printf("Process %d random available value: %d\n", i, available[i]);
//     }

//     // max, allocation, need 배열 초기화
//     for (i = 0; i < num_processes; i++) {
//         for (j = 0; j < NUM_RESOURCES; j++) {
//             max[i][j] = rand() % 10;
//             allocation[i][j] = rand() % (max[i][j] + 1);
//             need[i][j] = max[i][j] - allocation[i][j];
//         }
//     }

//     // 은행원 알고리즘 실행
//     bool is_safe = is_safe_state(available, max, allocation, need, num_processes);

//     // 결과 출력
//     for (i = 0; i < num_processes; i++) {
//         printf("Process %d random alloc value: %d max value : %d\n", i, allocation[i][0], max[i][0]);
//     }
//     printf("Safety: %s\n", is_safe ? "true" : "false");

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUM_RESOURCES 3

bool is_safe_state(int available[], int max[][NUM_RESOURCES], int allocation[][NUM_RESOURCES], int need[][NUM_RESOURCES], int num_processes) {
    bool finish[num_processes];
    int work[NUM_RESOURCES];
    int i, j;

    // 초기화
    for (i = 0; i < num_processes; i++)
        finish[i] = false;

    for (i = 0; i < NUM_RESOURCES; i++)
        work[i] = available[i];

    // 안전성 검사
    int count = 0;
    while (count < num_processes) {
        bool found = false;
        for (i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (j = 0; j < NUM_RESOURCES; j++)
                        work[j] += allocation[i][j];

                    finish[i] = true;
                    found = true;
                    count++;
                    break;
                }
            }
        }
        if (!found)
            break;
    }

    // 안전 상태 여부 반환
    if (count == num_processes)
        return true;
    else
        return false;
}

int main() {
    // 랜덤 값을 위한 시드 설정
    srand(time(NULL));

    int num_processes = 5;  // 프로세스 수

    int available[NUM_RESOURCES];
    int max[num_processes][NUM_RESOURCES];
    int allocation[num_processes][NUM_RESOURCES];
    int need[num_processes][NUM_RESOURCES];
    int i, j;

    // available 배열 초기화
    for (i = 0; i < NUM_RESOURCES; i++) {
        available[i] = rand() % 10;
    }

    // max, allocation, need 배열 초기화
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < NUM_RESOURCES; j++) {
            max[i][j] = rand() % 10;
            allocation[i][j] = rand() % (max[i][j] + 1);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // 은행원 알고리즘 실행
    bool is_safe = is_safe_state(available, max, allocation, need, num_processes);

    // 결과 출력
    printf("Process\tMax\tAllocation\tAvailable Resources\tNeed\n");
    printf("-------------------------------------------------------------------\n");
    for (i = 0; i < num_processes; i++) {
        printf("%d\t", i);
        for (j = 0; j < NUM_RESOURCES; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\t");
        for (j = 0; j < NUM_RESOURCES; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t\t");
        if (i == 2)
            for (j = 0; j < NUM_RESOURCES; j++) {
            printf("%d ", available[j]);
            }
        printf("\t\t\t");
        for (j = 0; j < NUM_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    printf("\nSafety: %s\n", is_safe ? "true" : "false");

    return 0;
}

