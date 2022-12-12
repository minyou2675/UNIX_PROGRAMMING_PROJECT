#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>


int main(){

	int pd[2];
	pid_t pid;
	char str[] = "Pipe test";
	char buf[BUFSIZ];
	int len, status;

	
	if(pipe(pd) == -1){
		perror("pipe");
		exit(1);
	}
	switch(pid = fork()){
	case -1 : 
		perror("fork");
		exit(1);
		break;
	case 0 :
	
	close(pd[1]);
	len = read(pd[0], buf, BUFSIZ);
	printf("%d read %s to the pipe.\n", (int)getpid(),buf);
	close(pd[0]);
	break;

	default:
	close(pd[0]);
	write(pd[1], str, strlen(str));
	printf("%d write %s from the pipe.\n", (int)getpid(),str);
	close(pd[1]);
	waitpid(pid, &status, 0);
	break;
	}
	return 0;


}
