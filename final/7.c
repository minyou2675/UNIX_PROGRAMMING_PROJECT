#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
int main(int argc, char* argv[]) {
    //공유 메모리로 사용할 파일기술자 생성
    int fd = shm_open("7", O_CREAT | O_RDWR, 0666);
    char buf[256];
    //fd의 파일 크기를 4096 바이트로 키움
    ftruncate(fd, 4096); 
    //ptr 변수에 메모리맵 할당
    char* ptr = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    pid_t pid ;
    int cnt = 0;
    close(fd);

    for(int i = 1; i < argc; i ++){
        char *temp = argv[i];
        strcat(buf,temp);
    }

    // Write a message to t
    strcpy(ptr, buf);

    // Create a child process
    switch(pid = fork()){
    case -1 : //자식 프로세스 생성 실패 시 에러처리
        perror("fork");
        exit(1);
    case 0 : // 자식 프로세스
        // This is the child process
	
        printf("Child process: %s\n", ptr);
        for(int i = 0; i < strlen(ptr); i++){
            if(isdigit(ptr[i]) !=  0){ //숫자가 있을 시 0 반환 
                cnt += ptr[i] - '0';
                    
                }
            }
	printf("sum : %d\n",cnt); 
        
        break;
    default: // 부모 프로세스
        
        wait(NULL); // 자식 프로세스 종료까지 대기
        munmap(ptr, 4096); // ptr에 매핑해제
        shm_unlink("7"); //공유 메모리 오브젝트 제거
    }

    return 0;
}
