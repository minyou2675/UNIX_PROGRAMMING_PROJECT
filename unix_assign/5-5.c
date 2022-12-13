#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>


int main(){

	int pd[2]; //파이프 생성 함수의 인자로 사용할 정수 2개 배열
	pid_t pid; // pid 저장 변수
	char str[] = "Pipe test"; //입출력 할 문자열
	char buf[BUFSIZ]; //입력을 받을 문자열
	int len, status; // len은 read와 write의 상태 값 return 받음, status은 wait을 위해 사용

	
	if(pipe(pd) == -1){ //파이프 생성 실패 시 -1 리턴 , 오류 메시지 출력 후 종료
		perror("pipe");
		exit(1);
	}
	switch(pid = fork()){ //자식 프로세스 생성
	case -1 : //프로세스 생성 실패 시 -1 반환 후, 오류 메시지 출력 후 종료 
		perror("fork"); 
		exit(1);
		break;
	case 0 : //자식 프로세스
	
	close(pd[1]); //쓰기 전용 파이프를 닫고 읽기 전용으로만 파이프 사용
	len = read(pd[0], buf, BUFSIZ); // 읽기 전용 파이프에 있는 문자열을 buf를 통해 읽어들임
	if(len == -1){ // 읽기 실패 시 에러호출 후 종료
		perror("read");
		exit(1)
	}
	printf("%d read %s to the pipe.\n", (int)getpid(),buf); // buf에 있는 내용과 자식 프로세스의 pid 출력
	close(pd[0]); //읽기 전용 파이프 닫음
	break; // 종료

	default: // 부모프로세스 
	close(pd[0]); // 읽기 전용 파이프를 닫고 쓰기 전용으로만 파이프 사용
	len = write(pd[1], str, strlen(str)); // str에 저장된 문자열을 문자열 크기만큼 쓰기 전용 파이프에 입력
	if(len == -1){ //쓰기 실패 시 에러호출 후 종료
		perror("write");
		exit(1);
	}
	printf("%d write %s from the pipe.\n", (int)getpid(),str);
	close(pd[1]); //쓰기 전용 파이프를 닫음
	waitpid(pid, &status, 0); // 자식  프로세스가 종료할 때까지 대기
	break; // 종료
	}
	return 0;


}
