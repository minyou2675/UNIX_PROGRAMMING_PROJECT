#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

    int fd[2];
    pid_t pid;
    char buf[255];
    int len, status;

    if(pipe(fd) == -1){

        perror("pipe");
        exit(1);
    }

    switch (pid = fork())
    {
    case -1 :
        perror("fork");
        exit(1);
    case 0 :
        close(fd[0]);
        if(fd[1] != 0){
            dup2(fd[1], 1);
            close(fd[1]);
        }
        execlp("ls", "ls", "-l",(char *)NULL);

        break;
    
    default:
        close(fd[1]);
        wait(NULL);
        if(fd[0] != 0){
            dup2(fd[0], 0);
            close(fd[0]);
        }
        execlp("grep","grep","c",(char *)NULL);
        exit(1);
        break;
    }




}
