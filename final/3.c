#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

   int shmid, i; //shmid는 공유메모리 생성 시 반환되는 값을 저장
   char *addr1, *addr2; //자식과 부모가 공유메모리에 연결할 주소공간
   pid_t pid;

   shmid = shmget(IPC_PRIVATE, 20, IPC_CREAT|0644); // 자식과 부모 프로세스 간 IPC로 한정 된 공유 메모리를 생성
   if(shmid == -1){ //공유 메모리 생성 실패 시 에러처리
   	perror("shmid");
	exit(1);
   }
    char buf[256]; // 결과에 출력할 메세지를 저장할 버퍼

    switch (pid = fork()) //자식 프로세스 생성
    {
    case -1 :
        perror("fork");
        exit(1);    
    case 0 :  //child process
    	addr1 = (char *)shmat(shmid, (char *)NULL, 0); // addr1에 공유 메모리를 연결
        printf("=Child %d begins\n",(int)getpid()); //getpid로 자식 pid 값을 정수로 반환하여 출력
        printf("=Child %d ends\n",(int)getpid());
        sprintf(buf,"%d gets Message from %d",(int)getppid(),(int)getpid()); //부모의 pid값과 자식 pid값을 정수로 포맷팅한 메세지를 앞에 선언한 전역 버퍼에 출력
        strcpy(addr1,buf); //addr1에 버퍼를 복사
        
        break;
    
    default: //parent process
        wait(NULL); //child process 종료 시까지 대기
	addr2 = (char *)shmat(shmid, (char *)NULL, 0); //addr2를 공유 메모리와 연결
        printf("=Parent %d begins\n",(int)getpid()); // 부모 자신의 pid를 정수 값으로 반환
        printf("%s\n",addr2); // addr2는 공유 메모리에 저장된 메세지 값을 담고 있고, 공유 메모리는 addr1의 내용을 가지고 있음.
        printf("=Parent %d ends\n", (int)getpid());
        exit(1); //종료
        break;
    }



}
