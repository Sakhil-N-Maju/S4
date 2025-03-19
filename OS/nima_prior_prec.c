#include <stdio.h>
void main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int pid[100], at[100], bt[100], ct[100], tt[100], wt[100], rt[100];
    int i, j,time = 0, completed = 0;
    float avg_wt = 0, avg_tt = 0;
    

    for (i = 0; i < n; i++) {
        printf("Enter the Process PID: ");
        scanf("%d", &pid[i]);
        printf("Enter the Process Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Enter the Process Burst time: ");
        scanf("%d", &bt[i]); 
        rt[i] = bt[i]; 
    }
     
    while (completed < n) {
        int selected_process = -1;
        int min_rt = 10000;  
        
        for (i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time && rt[i] < min_rt) {
                min_rt= rt[i];
                selected_process = i;
            }
        }
    
        if (selected_process != -1) {
            rt[selected_process]--;  
            time++;  
    
            
            if (rt[selected_process] == 0) {
                completed++;  
                ct[selected_process] = time; 
                tt[selected_process] = ct[selected_process] - at[selected_process]; 
                wt[selected_process] = tt[selected_process] - bt[selected_process]; 
            }
        } 
        else {
            time++; 
        }
    }
    
    for (i = 0; i < n; i++) {
        avg_wt= avg_wt+wt[i];
        avg_tt= avg_tt+tt[i];
    }

    avg_wt /= n;
    avg_tt /= n;

    
    printf("AVERAGE WAITING TIME: %f\n", avg_wt);
    printf("AVERAGE TURN-AROUND TIME: %f\n", avg_tt);
    ct[0]=0;

    
    printf("GANTT CHART \n");
    printf("____________________________________________________________________________________ \n");
    printf("|");
    for (i = 0; i < n; i++) {
        printf("	%d	|", pid[i]);
        
    }
    printf("\n");
    printf("____________________________________________________________________________________ \n");
    printf("|");
    for (i = 0; i < n; i++) {
        printf("	%d	|", ct[i]);
        
    }
    printf("\n");
}
