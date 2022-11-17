#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
	
	int status, i;
	int fd,fd2;
	char buf[100];
	pid_t pid;

	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}
	if(pid == 0){
		fd = open("4-5.txt",O_WRONLY | O_CREAT | O_TRUNC);
		if(fd == -1){
			perror("Create");
			exit(1);
		}
		printf("Child process excutes\n");
		printf("Child process pid:%d, parent process pid:%d\n",getpid(),getppid());

		fgets(buf,sizeof(buf),stdin);
		write(fd,buf,sizeof(buf));
		close(fd);
		
	}
	else{
		while(!wait(&status))
			continue;
		printf("Parent process excutes\n");
		printf("Parent process pid:%d\n",getpid());
		fd2 = open("4-5.txt",O_RDONLY);
		if(fd2 == -1){
			perror("Read");
			exit(2);
		}
		read(fd2,buf,sizeof(buf));
		fputs(buf,stdout);
		close(fd2);
		
	}
	printf("pid %d  process end\n",getpid());

}
