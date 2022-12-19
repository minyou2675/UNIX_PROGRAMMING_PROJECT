#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

    int fd;
    pid_t pid;
    caddr_t addr;
    struct stat statbuf;
    char buf[256];

    addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    if(addr == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
    close(fd);

    switch (pid = fork())
    {
    case : -1
        perror("fork");
        exit(1);    
    case : 0 //child process
        int child = (int)getpid();
        int parent = (int)getppid();
        printf("=Child %d begins\n",child);
        printf("=Child %d ends\n",child);
        sprintf(buf,"%d gets Message from %d",parent,child);
        strcpy(addr,buf);
        
        break;
    
    default:
        wait(NULL);
        printf("=Parent %d begins\n",(int)getpid());
        printf("%s\n",addr);
        printf("=Parent %d ends", (int)getpid());
        exit(1);
        break;
    }



}