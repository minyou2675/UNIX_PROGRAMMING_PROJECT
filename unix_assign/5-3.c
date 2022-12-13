#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int fd,status;
	pid_t pid;
	caddr_t addr;
	struct stat statbuf;

if (argc != 2){ //인자를 받지 않았을 경우 에러 처리
                perror("Usage:");
                exit(1);
        }
        if (stat(argv[1], &statbuf) == -1) //받은 인자 파일을 불러올 수 있는지 확인
        {
                perror("stat");
                exit(1);
        }
		 if((fd = open(argv[1], O_RDWR)) == -1){ //파일 기술자에 인자에 해당하는 파일 할당
                perror("open");
                exit(1);
        }
	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE,MAP_SHARED, fd, (off_t) 0); //addr에 fd에 있는 내용 매핑하고 실패 시 에러처리
	if (addr == MAP_FAILED){
		perror("mmap");
		exit(1);
	}
 
	
	switch(pid = fork()){ //자식 프로세스 생성
	  case -1 : // 프로세스 생성 실패 시 에러 처리
		  perror("fork");
		  exit(1);
		  break;
	case 0 : //자식 프로세스
	sleep(1); //1초간 프로세스 중지
	printf("%s\n", addr); //매핑한 문자열을 출력
	break; //종료

	default : // 부모 프로세스 
	waitpid(pid, &status, 0); //자식 프로세스 종료 대기
	close(fd); // 파일기술자 닫음
	break; //종료
	}
	

}


