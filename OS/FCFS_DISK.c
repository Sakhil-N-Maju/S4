#include<stdio.h>
#include<stdlib.h>

void main(){
	int n,queue[100],s=0;
	printf("Enter the lenth of the queue : ");
	scanf("%d",&n);
	printf("Enter the elements : ");
	for(int i=1;i<n;i++){
		scanf("%d",&queue[i]);
	}
	
	printf("Enter the initial position : ");
	scanf("%d",&queue[0]);
	
	for(int i=0;i<n;i++){
		int diff=abs(queue[i] - queue[i+1]);
		s+=diff;
		printf("\n Move from %d to %d and the seek is %d \n",queue[i],queue[i+1],diff);
	}
	
	printf("Total seek : %d",s);
	
}
