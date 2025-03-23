#include <stdio.h>
#include <stdbool.h>

void calculateNeed(int P, int R, int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
}

bool isSafe(int P, int R, int processes[], int avail[], int max[][R], int allot[][R], int safeSeq[]) {
    int need[P][R], work[R], finish[P];
    for (int i = 0; i < P; i++)
        finish[i] = 0;

    calculateNeed(P, R, need, max, allot);

    for (int j = 0; j < R; j++) 
        work[j] = avail[j];

    int count = 0;
    while (count < P) {
        bool found = false;

        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (int j = 0; j < R; j++) 
                        work[j] += allot[i][j];

                    safeSeq[count++] = processes[i];
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) return false;
    }
    return true;
}

bool canGrantRequest(int P, int R, int avail[], int need[P][R], int request[], int processID) {
    for (int j = 0; j < R; j++) {
        if (request[j] > need[processID][j] || request[j] > avail[j]) 
            return false;
    }
    return true;
}

int main() {
    int P, R;
    
    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resources: ");
    scanf("%d", &R);

    int processes[P], avail[R], max[P][R], allot[P][R], safeSeq[P];

    for (int i = 0; i < P; i++) 
        processes[i] = i;

    printf("Enter available resources: ");
    for (int j = 0; j < R; j++) 
        scanf("%d", &avail[j]);

    printf("Enter max resource matrix:\n");
    for (int i = 0; i < P; i++) 
        for (int j = 0; j < R; j++) 
            scanf("%d", &max[i][j]);

    printf("Enter allocated resource matrix:\n");
    for (int i = 0; i < P; i++) 
        for (int j = 0; j < R; j++) 
            scanf("%d", &allot[i][j]);

    if (isSafe(P, R, processes, avail, max, allot, safeSeq)) {
        printf("\nSystem is in a SAFE state.\nSafe sequence: ");
        for (int i = 0; i < P; i++) 
            printf("P%d ", safeSeq[i]);
    } else {
        printf("\nSystem is in an UNSAFE state. Deadlock is possible.\n");
    }

    int processID;
    printf("\nEnter process ID for resource request: ");
    scanf("%d", &processID);

    int request[R], need[P][R];
    calculateNeed(P, R, need, max, allot);

    printf("Enter resource request for process P%d: ", processID);
    for (int j = 0; j < R; j++) 
        scanf("%d", &request[j]);

    if (canGrantRequest(P, R, avail, need, request, processID)) {
        printf("The request CAN be granted immediately.\n");
    } else {
        printf("The request CANNOT be granted immediately.\n");
    }

    return 0;
}
