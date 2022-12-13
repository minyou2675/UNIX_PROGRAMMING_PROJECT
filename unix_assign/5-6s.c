#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(){

	int pd; //파일 기술자로 사용할 변수
	char str[] = "Pipe test"; // 입출력에 쓰일 문자열
	int len; // 입출력 상태 값 저장 할 변수
	
	if(mkfifo("./HAN-FIFO",0666) == -1) //읽고 쓰기 전용의 FIFO 파일 생성, 실패 시 에러메시지 호출 후 종료
	{
		perror("mkfifo");
		exit(1);
	}
	if((pd = open("./HAN-FIFO",O_WRONLY)) == -1){ //파일 기술자에 HAN-FIFO 할당 실패 시 에러메시지 호출 후 종료
		perror("open");
		exit(1);
	}
	len = write(pd,str, strlen(str)); // write 한 바이트 값 return 받음
	
	if(len == -1){ // 쓰기 실패 시 에러메시지 호출 후 종료
		perror("write");
		exit(1);
	}
	close(pd); //파일 기술자를 닫음
	printf("%d writes %s to the pipe.\n", (int)getpid(),str); //현재 프로세스와 문자열 출력
	
	return 0;
}
