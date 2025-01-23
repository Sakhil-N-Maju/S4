#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>
void main(){
	DIR *dir;
	struct dirent*p2;
	char dir_name[50];
	printf("enter dir name : ");
	scanf("%s",dir_name);
	dir = opendir(dir_name);
	while((p2 = readdir(dir)) != NULL){
		printf("%ld\t%s\n",p2->d_ino,p2->d_name);
	}
	closedir(dir);
}
