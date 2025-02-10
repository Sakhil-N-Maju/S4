#include<stdio.h>


void main(){
	int p[100],ct[100],tt[100],n,bt[100],wt[100],temp=0;
	float avg_tt=0.0,avg_wt=0.0;
	printf("ENTER THE NO OF PROCESS : ");
	scanf("%d",&n);
	printf("ENTER THE BURST TIME \n");
	for(int i=0;i<n;i++){
		p[i]=i+1;
		printf("p%d - ",i+1);
		scanf("%d",&bt[i]);
		
	}
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(bt[j]>bt[j+1]){
				temp=bt[j];
				bt[j]=bt[j+1];
				bt[j+1]=temp;
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;	
			}	
		}
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
	
	wt[0]=0;
	
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


















