#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

   int shmid, i;
   char *addr1, *addr2;
   pid_t pid;

   shmid = shmget(IPC_PRIVATE, 20, IPC_CREAT|0644);
   if(shmid == -1){
   	perror("shmid");
	exit(1);
   }
    char buf[256];

    switch (pid = fork())
    {
    case -1 :
        perror("fork");
        exit(1);    
    case 0 :  //child process
    	addr1 = (char *)shmat(shmid, (char *)NULL, 0);
        printf("=Child %d begins\n",(int)getpid());
        printf("=Child %d ends\n",(int)getpid());
        sprintf(buf,"%d gets Message from %d",(int)getppid(),(int)getpid());
        strcpy(addr1,buf);
        
        break;
    
    default:
        wait(NULL);
	addr2 = (char *)shmat(shmid, (char *)NULL, 0);
        printf("=Parent %d begins\n",(int)getpid());
        printf("%s\n",addr2);
        printf("=Parent %d ends\n", (int)getpid());
        exit(1);
        break;
    }



}
