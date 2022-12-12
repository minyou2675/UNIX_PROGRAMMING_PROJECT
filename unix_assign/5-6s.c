#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(){

	int pd;
	char str[] = "Pipe test";
	int len;
	
	if(mkfifo("./HAN-FIFO",0666) == -1)
	{
		perror("mkfifo");
		exit(1);
	}
	if((pd = open("./HAN-FIFO",O_WRONLY)) == -1){
		perror("open");
		exit(1);
	}
	len = write(pd,str, strlen(str));
	
	if(len == -1){
		perror("write");
		exit(1);
	}
	close(pd);
	printf("%d writes %s to the pipe.\n", (int)getpid(),str);
	
	return 0;
}
