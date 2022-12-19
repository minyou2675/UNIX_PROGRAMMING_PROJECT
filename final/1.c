#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int cnt = 0;

void sig_handler(int signo){
   cnt ++;
   fprintf(stderr,"CHanlder is called %d time(s)",cnt);

}

int main(){

    struct sigaction act;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_handler = sig_handler;
    if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0){
        perror("sigaction");
        exit(1);
   }

    while(1){
        printf("I'm in infinite loop");
        pause();
    }
}