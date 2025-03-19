#include <stdio.h>

void main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[100], at[100], bt[100], ct[100], tt[100], wt[100];
    int is_completed[100] = {0}, execution_order[100], exec_count = 0;
    int i, j, time = 0, completed = 0;
    float avg_wt = 0, avg_tt = 0;

    for (i = 0; i < n; i++) {
        printf("Enter the Process PID: ");
        scanf("%d", &pid[i]);
        printf("Enter the Process Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Enter the Process Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // Process Execution
    while (completed < n) {
        int shortest = -1, min_bt = 9999;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && is_completed[i] == 0 && bt[i] < min_bt) {
                min_bt = bt[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++; // CPU idle time
            continue;
        }

        execution_order[exec_count++] = pid[shortest]; // Store execution order
        time += bt[shortest];
        ct[shortest] = time;
        tt[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tt[shortest] - bt[shortest];

        is_completed[shortest] = 1;
        completed++;
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tt += tt[i];
    }
    avg_wt /= n;
    avg_tt /= n;

    // Process Table
    printf("\nPROCESS TABLE\n");
    printf("+-----+--------------+------------+----------------+-----------------+--------------+\n");
    printf("| PID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("+-----+--------------+------------+----------------+-----------------+--------------+\n");
    for (i = 0; i < n; i++) {
        printf("| %3d | %12d | %10d | %14d | %15d | %12d |\n",
               pid[i], at[i], bt[i], ct[i], tt[i], wt[i]);
    }
    printf("+-----+--------------+------------+----------------+-----------------+--------------+\n");

    printf("\nAVERAGE WAITING TIME: %.2f\n", avg_wt);
    printf("AVERAGE TURNAROUND TIME: %.2f\n", avg_tt);

    // Gantt Chart
    printf("\nGANTT CHART\n");
    printf("-------------------------------------------------------------------\n");
    printf("|");

    time = 0;
    for (i = 0; i < exec_count; i++) {
        printf(" P%d |", execution_order[i]);
    }
    
    printf("\n-------------------------------------------------------------------\n");

    // Printing time below Gantt Chart
    printf("0");
    time = 0;
    for (i = 0; i < exec_count; i++) {
        for (j = 0; j < n; j++) {
            if (pid[j] == execution_order[i]) {
                time += bt[j];
                printf("   %d", time);
                break;
            }
        }
    }
    printf("\n");
}
