#include <stdio.h>

void main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[100], at[100], bt[100], bt_rem[100], ct[100], tt[100], wt[100];
    int i, time = 0, completed = 0, min_bt, shortest, finish_time;
    float avg_wt = 0, avg_tt = 0;
    int is_completed[100] = {0};

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

        for (i = 0; i < n; i++) {
            if (at[i] <= time && !is_completed[i] && bt_rem[i] < min_bt) {
                min_bt = bt_rem[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        bt_rem[shortest]--;

        if (bt_rem[shortest] == 0) {
            completed++;
            finish_time = time + 1;
            ct[shortest] = finish_time;
            tt[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tt[shortest] - bt[shortest];
            is_completed[shortest] = 1;
        }

        time++;
    }

    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tt += tt[i];
    }

    avg_wt /= n;
    avg_tt /= n;

    printf("\nPROCESS TABLE\n");
    printf("----------------------------------------------------------------------------------------------\n");
    printf("| PID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("----------------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("| %3d | %12d | %10d | %14d | %15d | %12d |\n",
                pid[i], at[i], bt[i], ct[i], tt[i], wt[i]);
    }
    printf("----------------------------------------------------------------------------------------------\n");

    printf("\nAVERAGE WAITING TIME: %.2f\n", avg_wt);
    printf("AVERAGE TURNAROUND TIME: %.2f\n", avg_tt);

    printf("\nGANTT CHART\n");
    printf("-------------------------------------------------------------------\n");
    int last_executed = -1;
    
    for (i = 0; i < time; i++) {
        int shortest = -1, min_bt = 9999;

        for (int j = 0; j < n; j++) {
            if (at[j] <= i && !is_completed[j] && bt_rem[j] < min_bt) {
                min_bt = bt_rem[j];
                shortest = j;
            }
        }

        if (shortest != -1 && shortest != last_executed) {
            printf("| P%d ", pid[shortest]);
            last_executed = shortest;
        }
    }
    printf("|\n");
    printf("-------------------------------------------------------------------\n");

    printf("0");
    for (i = 0; i < time; i++) {
        int shortest = -1, min_bt = 9999;
        
        for (int j = 0; j < n; j++) {
            if (at[j] <= i && !is_completed[j] && bt_rem[j] < min_bt) {
                min_bt = bt_rem[j];
                shortest = j;
            }
        }

        if (shortest != -1) {
            printf("   %d", i + 1);
        }
    }
    printf("\n");
}

