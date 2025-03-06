#include<sys/ipc.h>
#include<sys/shm.h>
# include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

void main(){
	int id;
	void *sm;
	char buff[100];
	id=shmget((key_t)1222,1024,0666);
	printf("key of shared memory = %d\n",id);
	sm=shmat(id,NULL,0);
	printf("process = %p\n",sm);
	printf("data read from memory = %s\n",(char *)sm);
	strcpy(buff,sm);
	int a=buff[0]-'0';
	int b =buff[2]-'0';
	printf("SUM = %d",a+b);
}
