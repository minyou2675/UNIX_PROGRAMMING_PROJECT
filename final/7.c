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
    //fd의 파일 크기를 4096 바이트로 키움
    ftruncate(fd, 4096); 
    //ptr 변수에 메모리맵 할당
    char* ptr = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    pid_t pid ;
    close(fd);

    // Write a message to t
    strcpy(ptr, "Hello from the parent!");

    // Create a child process
    switch(pid = fork()){
    case -1 : //자식 프로세스 생성 실패 시 에러처리
        perror("fork");
        exit(1);
    case 0 : // 자식 프로세스
        // This is the child process
        printf("Child process: %s\n", ptr);
    default: // 부모 프로세스
        printf("Parent process: %s\n", ptr);
        wait(NULL); // 자식 프로세스 종료까지 대기
        munmap(ptr, 4096);
        shm_unlink("7"); //공유 메모리 해제
    }

    return 0;
}
