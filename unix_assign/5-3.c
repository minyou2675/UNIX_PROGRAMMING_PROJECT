#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int fd,status;
	pid_t pid;
	caddr_t addr;
	struct stat statbuf;

if (argc != 2){
                perror("Usage:");
                exit(1);
        }
        if (stat(argv[1], &statbuf) == -1)
        {
                perror("stat");
                exit(1);
        }
        if((fd = open(argv[1], O_RDWR)) == -1){
                perror("open");
                exit(1);
        }
	
	switch(pid = fork()){
	  case -1 :
		  perror("fork");
		  exit(1);
		  break;
	case 0 :
	sleep(5);
	printf("%s\n", addr);
	break;

	default :
	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE,MAP_SHARED, fd, (off_t) 0);
	if (addr == MAP_FAILED){
		perror("mmap");
		exit(1);
	}
	close(fd);
	printf("%s\n",addr);

	waitpid(pid, &status, 0);
	break;
	}
	

}


