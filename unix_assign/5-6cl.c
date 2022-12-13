#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(){

	int pd,len; // 파일 기술자와 read 상태 값 저장 할 변수 선언
	char buf[BUFSIZ]; // read를 통해 문자열을 저장 할 배열 선언
	
	if((pd = open("./HAN-FIFO",O_RDONLY)) == -1){ //읽기 전용으로 HAN-FIFO를 파일 기술자에 할당 실패 시 에러메시지 호출 후 종료
		perror("open");
		exit(1);
	}
	len = read(pd,buf,BUFSIZ); // HAN-FIFO의 내용을 buf 배열을 통해 읽어 들이고 바이트 값을 len에 저장
	
	if(len == -1){ // 읽기 실패 시 에러메시지 호출 후 종료
		perror("read");
		exit(1);
	}
	close(pd); // 파일 기술자 닫음

	printf("%d reads %s from the pipe. \n",(int)getpid(),buf); //현재 프로세스와 읽어 들인 내용을 저장한 buf에 문자열 출력
	
	return 0;
}
