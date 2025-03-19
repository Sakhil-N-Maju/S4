#include <stdio.h>

void main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    int pid[100], at[100], bt[100], ct[100], tt[100], wt[100], rt[100], queue[100];
    int i, time = 0, completed = 0, front = 0, rear = 0;
    float avg_wt = 0, avg_tt = 0;
    
    // Input for processes, burst times, and arrival times
    for (i = 0; i < n; i++) {
        printf("Enter the Process PID: ");
        scanf("%d", &pid[i]);
        printf("Enter the Process Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Enter the Process Burst Time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Remaining burst time
    }

    // Sort processes based on arrival time (for fairness)
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                // Swap Arrival Time
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                // Swap Burst Time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap PID
                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;

                // Swap Remaining Time
                temp = rt[j];
                rt[j] = rt[j + 1];
                rt[j + 1] = temp;
            }
        }
    }

    // Initialize queue and push first process
    queue[rear++] = 0;

    int gantt_order[200], gantt_time[200], gantt_index = 0;
    
    // Main loop for Round Robin Scheduling
    while (completed < n) {
        int all_done = 1;
        
        for (i = 0; i < rear; i++) {
            int idx = queue[i];

            if (rt[idx] > 0) {
                all_done = 0;
                
                // Execute process for time quantum or remaining burst time
                if (rt[idx] > quantum) {
                    time += quantum;
                    rt[idx] -= quantum;
                } else {
                    time += rt[idx];
                    ct[idx] = time;
                    rt[idx] = 0;  // Process completed
                    tt[idx] = ct[idx] - at[idx];  // Turnaround time
                    wt[idx] = tt[idx] - bt[idx];  // Waiting time
                    completed++;  // Increase completed process count
                }

                // Add to Gantt Chart
                gantt_order[gantt_index] = pid[idx];
                gantt_time[gantt_index++] = time;

                // Add new processes that arrived during execution
                for (int j = 0; j < n; j++) {
                    if (at[j] <= time && rt[j] > 0) {
                        int already_in_queue = 0;
                        for (int k = 0; k < rear; k++) {
                            if (queue[k] == j) {
                                already_in_queue = 1;
                                break;
                            }
                        }
                        if (!already_in_queue) {
                            queue[rear++] = j;
                        }
                    }
                }

                // Re-add process to queue if not completed
                if (rt[idx] > 0) {
                    queue[rear++] = idx;
                }
            }
        }

        // If no process is ready, increment time
        if (all_done) {
            time++;
        }
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tt += tt[i];
    }

    avg_wt /= n;
    avg_tt /= n;

    // Output results
    printf("\nPROCESS TABLE\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("| PID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("| %3d | %12d | %10d | %15d | %15d | %12d |\n",
                pid[i], at[i], bt[i], ct[i], tt[i], wt[i]);
    }
    printf("------------------------------------------------------------------------------------\n");

    // Output the averages
    printf("\nAVERAGE WAITING TIME: %.2f\n", avg_wt);
    printf("AVERAGE TURNAROUND TIME: %.2f\n", avg_tt);

    // Print Gantt Chart
    printf("\nGANTT CHART\n ");
    
    // Top line
    for (i = 0; i < gantt_index; i++) {
        printf("----");
    }
    printf("-\n|");

    // Process execution order
    for (i = 0; i < gantt_index; i++) {
        printf(" P%d |", gantt_order[i]);
    }
    printf("\n ");

    // Bottom line
    for (i = 0; i < gantt_index; i++) {
        printf("----");
    }
    printf("-\n0");

    // Time values
    for (i = 0; i < gantt_index; i++) {
        printf("   %d", gantt_time[i]);
    }
    printf("\n");
}
