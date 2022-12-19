#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int cnt = 0; //signal이 들어온 횟수는 전역변수로 선언함

void sig_handler(int signo){ //
   cnt ++; //signal이 들어올 때마다 함수가 실행되면서 횟수를 추가
   printf("CHanlder is called %d time(s)\n",cnt); //몇 번 불렀는지 출력

}

int main(){

    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = sig_handler; //act가 signal을 받았을 때 handler로 사용할 함수 지정
    if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0){ // SIGINT를 받았을 때 act에 정의된 대로 sig_hanlder 함수를 실행하고, 리턴 값이 음수가 나오면 에러 처리
        perror("sigaction");
        exit(1);
   }

    while(1){ //무한루프로 진입하게 함
        fprintf(stderr,"I'm in infinite loop\n"); // 처음 시작하고 sig_handler가 끝날 때마다 이 문장 반복 
        pause(); //signal이 올 때까지 대기
    }
}
