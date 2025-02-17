#include<stdio.h>
void main(){
	int n;
	printf("ENTER THE NO: OF PROCESS : ");
	scanf("%d",&n);
	int pid[100],at[100],bt[100],ct[100],tt[100],wt[100],rt[100],prio[100];
	int time=0,complete=0,temp;
	float avg_tt=0.0,avg_wt=0.0;
	printf("ENTER THE PROCESS DETAILS \n");
	for(int i=0;i<n;i++){
		printf("ENTER FOR PROCESS p%d\n",i+1);
		pid[i]=i+1;
		printf("at : ");
		scanf("%d",&at[i]);
		printf("bt : ");
		scanf("%d",&bt[i]);
		rt[i]=bt[i];
		printf("priority : ");
		scanf("%d",&prio[i]);
		
	}
	
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(prio[j] >= prio[j+1] ){
				temp=prio[j];
				prio[j]=prio[j+1];
				prio[j+1]=temp;
				
				temp=pid[j];
				pid[j]=pid[j+1];
				pid[j+1]=temp;
				
				temp=at[j];
				at[j]=at[j+1];
				at[j+1]=temp;
				
				temp=bt[j];
				bt[j]=bt[j+1];
				bt[j+1]=temp;
				
				temp=rt[j];
				rt[j]=rt[j+1];
				rt[j+1]=temp;
				
			}
		}
	}
	
	while(complete < n){
		int highest_prio = 10000;
		int process = -1;
		
		for(int i=0;i<n;i++){
			if(rt[i]>0 && at[i]<=time && prio[i]<highest_prio){
				highest_prio=prio[i];
				process=i;
			}	
		}		
		if(process != -1){
			time++;
			rt[process]--;
			
			if(rt[process]==0){
				complete++;
				ct[process]=time;
				tt[process]=ct[process]-at[process];
				wt[process]=tt[process]-bt[process];
			}
		}
		else{
				time++;
			}
		
	}
	
	for(int i=0;i<n;i++){
		avg_tt+=tt[i];
		avg_wt+=wt[i];
	}
	
	printf("AVERAGE TT = %f\n", avg_tt/n);
	printf("AVERAGE WT = %f\n",avg_wt/n);
	
	printf("\n-------------------------------------------------------------------------------------------------------------------------\n");
	printf("PID\t\tAT\t\tBT\t\tPRIORITY\t\tCT\t\tTT\t\tWT\t\n");
	printf("\n-------------------------------------------------------------------------------------------------------------------------\n");
	for(int i=0;i<n;i++){
		printf("p%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\n",pid[i],at[i],bt[i],prio[i],ct[i],tt[i],wt[i]);
	}
	printf("\n-------------------------------------------------------------------------------------------------------------------------\n");
}
