#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
void main(){
	int p1,p2;
	char w[100];
	char r[100];
	p1 = open("file.txt",O_RDWR);
	printf("enter contents to write : ");
	scanf("%s",w);
	write(p1,w,strlen(w));
	close(p1);
	p2 = open("file.txt",O_RDWR);
	printf("contents of the file : ");
	read(p2,r,100);
	printf("%s",r);
	close(p2);
	
}
