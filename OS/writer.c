#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void main(){
	int id;
	void *sm;
	char buff[100];
	id=shmget((key_t)1222,1024,0666);
	printf("key of shared memory = %d\n",id);
	sm=shmat(id,NULL,0);
	printf("process = %p\n",sm);
	printf("Enter the data to be written");
	read(0,buff,100);
	strcpy(sm,buff);
	printf("Data written =%s",(char *)sm);
}
