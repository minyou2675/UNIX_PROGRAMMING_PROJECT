#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int fd; //파일 기술자로 사용할 변수 선언
	caddr_t addr; //매핑할 주로
	struct stat statbuf;

	if (argc != 2){ //인자를 받지 않을 시 에러처리
		perror("Usage:");
		exit(1);
	}
	if (stat(argv[1], &statbuf) == -1) //파일의 정보를 statbuf에 저장, 실패 시 에러 호출
	{
		perror("stat");
		exit(1);
	}
	if((fd = open(argv[1], O_RDWR)) == -1){ // 파일 기술자에 인자로 받은 파일을 읽고쓰기 전용으로 할당 에러 시 에러메시지 호출
		perror("open");
		exit(1);
	}

	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE,MAP_SHARED, fd, (off_t) 0); 
	// addr에 파일 기술자가 읽어들인 값을 파일 사이즈 만큼 읽고 쓰기 전용으로 매핑, 다른 사용자와 데이터 변경 내용 공유, 오프셋 값 0
	if (addr == MAP_FAILED){ // addr에 매핑 실패 시 에러 호출
		perror("mmap");
		exit(1);
	}
	close(fd); // 파일 기술자 닫음

	printf("%s", addr); // 매핑 된 내용을 출력



}
