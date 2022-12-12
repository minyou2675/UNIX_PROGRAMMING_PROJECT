#include <unistd.h> //POSIX 표준 상수와 함수 사용 
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //strlen 함수 사용


int main(){

	int pd[2]; //파이프 함수의 인자로 쓰일 정수형 배열 선언
	char str[] = "Pipe test"; //읽고 출력할 문자열 선언
	char buf[BUFSIZ]; // 파이프에서 내용을 read할 배열
	int len, status;  

	if(pipe(pd) == -1){ // pipe에 파일 기술자 2개 저장, 실패로 -1 반환시 에러메시지 호출
		perror("pipe");
		exit(1);
	}
	status = write(pd[1],str, strlen(str)); // 쓰기 전용 파이프에 문자열의 크기 만큼 문자열 저장
	
	if(status == -1){ // 쓰기 실패 시 에러 메시지 출력 후 종료
		perror("write");
		exit(1); 
	}
	
	printf("%d writes %s to the pipe.\n", (int)getpid(),str); 
	len = read(pd[0],buf,BUFSIZ); // 읽기 전용 파이프를 통해 저장된 문자열을 buf로 읽어옴

	if(len == -1){ // 읽기 실패 시 에러 메시지 출력 후 종료
		perror("read");
		exit(1);
	}
	printf("%d reads %s from the pipe. \n",(int)getpid(),buf);

	// 
	close(pd[0]);
	close(pd[1]);
	
	return 0;
}
