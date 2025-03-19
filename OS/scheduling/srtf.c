#include <stdio.h>

void main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[100], at[100], bt[100], bt_rem[100], ct[100], tt[100], wt[100];
    int i, time = 0, completed = 0, min_bt, shortest;
    float avg_wt = 0, avg_tt = 0;
    int is_completed[100] = {0};
    
    // Gantt chart tracking
    int gantt_pid[1000], gantt_time[1000], gantt_idx = 0;

    // Input processes
    for (i = 0; i < n; i++) {
        printf("Enter the Process PID: ");
        scanf("%d", &pid[i]);
        printf("Enter the Process Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Enter the Process Burst time: ");
        scanf("%d", &bt[i]);
        bt_rem[i] = bt[i];
    }

    while (completed != n) {
        shortest = -1;
        min_bt = 9999;

        // Find process with shortest remaining time
        for (i = 0; i < n; i++) {
            if (at[i] <= time && !is_completed[i] && bt_rem[i] < min_bt) {
                min_bt = bt_rem[i];
                shortest = i;
            }
        }

        // If no process is available, CPU is idle
        if (shortest == -1) {
            time++;
            continue;
        }

        // Store Gantt chart execution order
        if (gantt_idx == 0 || gantt_pid[gantt_idx - 1] != pid[shortest]) {
            gantt_pid[gantt_idx] = pid[shortest];
            gantt_time[gantt_idx] = time;
            gantt_idx++;
        }

        // Process execution
        bt_rem[shortest]--;

        // If process is completed
        if (bt_rem[shortest] == 0) {
            completed++;
            ct[shortest] = time + 1;
            tt[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tt[shortest] - bt[shortest];
            is_completed[shortest] = 1;
        }

        time++;
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tt += tt[i];
    }
    avg_wt /= n;
    avg_tt /= n;

    // Print Process Table
    printf("\nPROCESS TABLE\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("| PID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("--------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("| %3d | %12d | %10d | %14d | %15d | %12d |\n",
                pid[i], at[i], bt[i], ct[i], tt[i], wt[i]);
    }
    printf("--------------------------------------------------------------------------------------\n");

    printf("\nAVERAGE WAITING TIME: %.2f\n", avg_wt);
    printf("AVERAGE TURNAROUND TIME: %.2f\n", avg_tt);

    // Print Gantt Chart
    printf("\nGANTT CHART\n");
    printf("----------------------------------------------------------------------------------\n");
    for (i = 0; i < gantt_idx; i++) {
        printf("| P%d ", gantt_pid[i]);
    }
    printf("|\n");
    printf("----------------------------------------------------------------------------------\n");

    for (i = 0; i < gantt_idx; i++) {
        printf("%d    ", gantt_time[i]);
    }
    printf("%d\n", time);
}
