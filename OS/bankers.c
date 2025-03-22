#include <stdio.h>
#include <stdbool.h>

void calculateNeed(int P, int R, int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

bool isSafe(int P, int R, int processes[], int avail[], int max[][R], int allot[][R], int safeSeq[]) {
    int need[P][R];
    calculateNeed(P, R, need, max, allot);
    
    bool finish[P];
    for (int i = 0; i < P; i++) finish[i] = false;
    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = avail[i];
    
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;
                
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];
                    safeSeq[count++] = processes[p];
                    finish[p] = true;
                    found = true;
                }
            }
        }
        
        if (!found) {
            return false;
        }
    }
    return true;
}

bool requestResources(int P, int R, int process, int request[], int avail[], int max[P][R], int allot[P][R]) {
    int need[P][R];
    calculateNeed(P, R, need, max, allot);
    
    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i] || request[i] > avail[i]) {
            printf("Request cannot be granted immediately.\n");
            return false;
        }
    }
    
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        allot[process][i] += request[i];
        need[process][i] -= request[i];
    }
    
    int safeSeq[P];
    if (!isSafe(P, R, (int[]){0, 1, 2, 3, 4}, avail, max, allot, safeSeq)) {
        for (int i = 0; i < R; i++) {
            avail[i] += request[i];
            allot[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request cannot be granted as it leads to an unsafe state.\n");
        return false;
    }
    printf("Request can be granted.\n");
    return true;
}

int main() {
    int P, R;
    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resources: ");
    scanf("%d", &R);
    
    int processes[P];
    for (int i = 0; i < P; i++)
        processes[i] = i;
    
    int available[R];
    printf("Enter available resources: ");
    for (int i = 0; i < R; i++)
        scanf("%d", &available[i]);
    
    int max[P][R], allocation[P][R];
    printf("Enter max resource matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &max[i][j]);
    
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);
    
    int safeSeq[P];
    if (isSafe(P, R, processes, available, max, allocation, safeSeq)) {
        printf("System is in a safe state. Safe sequence is: ");
        for (int i = 0; i < P; i++)
            printf("%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("System is not in a safe state.\n");
    }
    
    int process;
    printf("Enter process number making request: ");
    scanf("%d", &process);
    int request[R];
    printf("Enter resource request for process %d: ", process);
    for (int i = 0; i < R; i++)
        scanf("%d", &request[i]);
    
    requestResources(P, R, process, request, available, max, allocation);
    
    return 0;
}
