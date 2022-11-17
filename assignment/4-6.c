#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void sig_handler(int signo)
{
	sleep(5);
}



int main(void){
	int status, i;
	pid_t pid;
	int fd, fd2;
	char buf[100];
	void (*hand) (int);
	hand = signal(SIGTTIN,sig_handler);

	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}
	if(pid == 0){
		sleep(10);
		printf("Child process excutes pid : %d\n",getpid());
		fd2 = open("4-6.txt",O_RDONLY);
		read(fd2,buf,sizeof(buf));
		fputs(buf,stdout);
		close(fd2);
	
	} 
	else{	
	
	printf("Parent process excutes pid : %d\n",getpid());
	fd = open("4-6.txt",O_WRONLY|O_TRUNC|O_CREAT);
	fgets(buf,sizeof(buf),stdin);
	write(fd,buf,sizeof(buf));
	close(fd);
	wait(&status);

	}
       printf("pid %d : process end\n",getpid());	



} 
