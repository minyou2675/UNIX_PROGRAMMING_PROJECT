#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    //공유 메모리로 사용할 파일기술자 생성
    int fd = shm_open("7", O_CREAT | O_RDWR, 0666);
    char buf[256];
    //fd의 파일 크기를 4096 바이트로 키움
    ftruncate(fd, 4096); 
    //ptr 변수에 메모리맵 할당
    char* ptr = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    pid_t pid ;
    close(fd);

    for(int i = 0; i < argc; i ++){
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
            if(isdigit(ptr[i]) == 0){ //숫자가 있을 시 0 반환 
                for(int j=i; j < strlen(ptr)-1; j++){ //숫자 제거하고 뒤에 문자열을 앞으로 당김
                    temp = ptr[j + 1];
                    ptr[j] = temp;
                    
                }
            }
            else
            continue;
        }
        break;
    default: // 부모 프로세스
        
        wait(NULL); // 자식 프로세스 종료까지 대기
        printf("Parent process: %s\n", ptr); //자식 프로세스가 가공한 문자를 출력
        munmap(ptr, 4096); // ptr에 매핑해제
        shm_unlink("7"); //공유 메모리 오브젝트 제거
    }

    return 0;
}
