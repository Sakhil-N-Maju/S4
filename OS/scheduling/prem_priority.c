#include <stdio.h>

void main() {
    int n, time = 0, completed = 0;
    float avg_wt = 0, avg_tt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[100], at[100], bt[100], priority[100], ct[100], tt[100], wt[100], remaining_bt[100];
    int execution_order[200], exec_count = 0, last_exec_pid = -1;

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter Process PID: ");
        scanf("%d", &pid[i]);
        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Enter Priority: ");
        scanf("%d", &priority[i]);

        remaining_bt[i] = bt[i]; // Initialize remaining burst time
    }

    // Process Execution (Preemptive)
    while (completed < n) {
        int highest_priority = 9999, selected_process = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && remaining_bt[i] > 0 && priority[i] < highest_priority) {
                highest_priority = priority[i];
                selected_process = i;
            }
        }

        if (selected_process == -1) {
            time++; // CPU is idle
            continue;
        }

        // Store execution order (only if process changes)
        if (last_exec_pid != pid[selected_process]) {
            execution_order[exec_count++] = pid[selected_process];
            last_exec_pid = pid[selected_process];
        }

        remaining_bt[selected_process]--;
        time++;

        // If process is completed
        if (remaining_bt[selected_process] == 0) {
            ct[selected_process] = time;
            tt[selected_process] = ct[selected_process] - at[selected_process];
            wt[selected_process] = tt[selected_process] - bt[selected_process];
            avg_wt += wt[selected_process];
            avg_tt += tt[selected_process];
            completed++;
        }
    }

    avg_wt /= n;
    avg_tt /= n;

    // Process Table
    printf("\nPROCESS TABLE\n");
    printf("+-----+--------------+------------+----------+----------------+-----------------+--------------+\n");
    printf("| PID | Arrival Time | Burst Time | Priority | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("+-----+--------------+------------+----------+----------------+-----------------+--------------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %3d | %12d | %10d | %8d | %14d | %15d | %12d |\n",
               pid[i], at[i], bt[i], priority[i], ct[i], tt[i], wt[i]);
    }
    printf("+-----+--------------+------------+----------+----------------+-----------------+--------------+\n");

    printf("\nAVERAGE WAITING TIME: %.2f\n", avg_wt);
    printf("AVERAGE TURNAROUND TIME: %.2f\n", avg_tt);

    // Gantt Chart
    printf("\nGANTT CHART\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("|");
    for (int i = 0; i < exec_count; i++) {
        printf(" P%d |", execution_order[i]);
    }
    printf("\n------------------------------------------------------------------------------------\n");

    // Printing time below Gantt Chart
    printf("0");
    time = 0;
    for (int i = 0; i < exec_count; i++) {
        for (int j = 0; j < n; j++) {
            if (pid[j] == execution_order[i]) {
                time++;
                printf("   %d", time);
                break;
            }
        }
    }
    printf("\n");
}
