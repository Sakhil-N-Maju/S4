#include<stdio.h>

/*struct process{
	int p_id;
	int at;
	int bt;
	int ct;
	int tt;
	int wt;
}p;
void addprocess(struct p[100],int n){
	for(int i=0;i<n;i++){
		printf("Enter process_id :");
		scanf("%d",&p[i].p_id);
		printf("Enter arival time :");
		scanf("%d",&p[i].at);
		printf("Enter burst time :");
		scanf("%d",&p[i].bt);
	}
	printf("The Input Table is :");
	printf("P_id\tAT\tBT");
	for(int i=0;i<n;i++){
		printf("P%d\t%d\t%d",&p[i].p_id,&p[i].at,&p[i].bt);
	}	
}
/*void sort(int p[100],int n){
	int temp;
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			temp = p[j].at;
			p[j].at=p[j+1].at;
			p[j+1].at=temp;	
		}
	}
}


void main(){
	int p[100];
	int n;
	printf("Enter the No: of Processes :");
	scanf("%d",&n);
	addprocess(p,n);
	//sort(p,n);
}


void main(){
	int pid[100],at[100],bt[100],ct[100],tt[100],wt[100];
	int n;
	printf("ENTER NO OF PROCESS");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		printf("ENTER PID,AT,BT");
		scanf("%d",&pid[i]);
		scanf("%d",&at[i]);
		scanf("%d",&bt[i]);
		
	}
	printf("PID\tAT\tBT\n");
	for(int i=0;i<n;i++){
		printf("P%d\t%d\t%d\n",pid[i],at[i],bt[i]);
	}		
}*/



void main(){
	int p[100],ct[100],tt[100],n,bt[100],wt[100];
	float avg_tt=0,avg_wt=0;
	printf("ENTER THE NO OF PROCESS : ");
	scanf("%d",&n);
	printf("ENTER THE BURST TIME \n");
	for(int i=0;i<n;i++){
		p[i]=i+1;
		printf("p%d - ",i+1);
		scanf("%d",&bt[i]);
		
	}
	printf("P_ID\tBT\n");
	for(int i=0;i<n;i++){
		printf("P%d\t%d",p[i],bt[i]);
		printf("\n");
	}	
	
	printf("\t\t\t\tGANTT CHART\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("||");
	for(int i=0;i<n;i++){
		printf("\tp%d\t||",p[i]);
		
	}
	printf("\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("||");
	for(int i=0;i<n;i++){
		printf("\t%d\t||",bt[i]);
		
	}
	printf("\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
	printf("\n");	
	
	for(int i=0;i<n;i++){
		wt[i]=bt[i-1]+wt[i-1];
		avg_wt=avg_wt+wt[i];
	}
	printf("AVERAGE WT = %f\n",avg_wt/n);
	
	for(int i=0;i<n;i++){
		tt[i]=bt[i]+wt[i];
		avg_tt=avg_tt+tt[i];
	}
	printf("AVERAGE TT = %f",avg_tt/n);
	
	
	
	
}


















