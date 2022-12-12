#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(){

	int pd,len;
	char buf[BUFSIZ];
	
	if((pd = open("./HAN-FIFO",O_RDONLY)) == -1){
		perror("open");
		exit(1);
	}
	len = read(pd,buf,BUFSIZ);
	
	if(len == -1){
		perror("read");
		exit(1);
	}
	close(pd);

	printf("%d reads %s from the pipe. \n",(int)getpid(),buf);
	
	return 0;
}
