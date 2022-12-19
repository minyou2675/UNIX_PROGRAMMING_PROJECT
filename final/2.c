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

    switch (pid = fork()) //자식 프로세스 생성
    {
    case -1 : //프로세스 생성 실패시 에러처리
        perror("fork"); 
        exit(1);
    case 0 : //자식 프로세스
        close(fd[0]); // 쓰기 전용 파이프로 선언
        if(fd[1] != 0){ 
            dup2(fd[1], 1); //파이프의 출력 부분을 표준 출력으로 복사
            close(fd[1]); //파이프는 필요 없으므로, 출력 파이프 닫음
        }
        execlp("ls", "ls", "-l",(char *)NULL); //ls -l을 실행, 출력 내역은 pipe로 전달되고 부모 프로세스가 입력 파이프로 읽어 들이게 함

        break;
    
    default: //부모 프로세스
        close(fd[1]); // 읽기 전용 파이프로 선언
        wait(NULL); //자식 프로세스 종료 시까지 대기
        if(fd[0] != 0){
            dup2(fd[0], 0); //표준 입력을 파이프에 복사
            close(fd[0]); // 읽기 전용 파이프 닫음
        }
        execlp("grep","grep","c",(char *)NULL); //grep 명령은 표준 입력으로 데이터를 읽어 들이려 하고, 표준 입력으로는 파이프의 입력 파일 기술자를 복사했으므로 파이프를 통해 데이터를 읽어 들임
        exit(1);
        break;
    }




}
