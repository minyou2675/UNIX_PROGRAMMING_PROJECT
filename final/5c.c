#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 8000

int main(int argc, char* argv[]){

    int sd; //소켓 기술자로 지정할 변수
    char buf[256]; //서버로 보낼 메시지를 저장
    char received[256]; //서버로부터 받는 메세지를 저장할 공간
    struct sockaddr_in sin; // 소켓 구조체를 선언하여 소켓의 종류, ip 주소, 포트 번호를 지정할 수 있도록 함.

   strcpy(buf,argv[1]); // 인자로 받은 문자를 buf에 저장

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ //소켓 생성하고 실패 시 에러처리
        perror("socket");
        exit(1);
    }

    memset((char *)&sin, '\0', sizeof(sin)); //sin 메모리의 값을 초기화 하고 소켓 구조체를 정의
    sin.sin_family = AF_INET;  
    sin.sin_port = htons(PORTNUM); //연결할 포트 번호
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); //연결할 ip 주소

    if(connect(sd, (struct sockaddr *)&sin, sizeof(sin)) == -1){ //지정한 ip주소로 연결을 시도하고 실패할 시 에러처리
        perror("connect");
        exit(1);
    }
    if(send(sd,buf,strlen(buf)+1, 0) == -1){ //buf에 저장된 메세지를 보냄 size는 문자열 길이에 + 종료문자 실패 시 에러처리
        perror("send");
        exit(1);
    }

    if(recv(sd, received, sizeof(received), 0) == -1){ //received 배열을 통해 서버가 처리한 메세지를 전달 받고 실패 시 에러처리
        perror("recv");
        exit(1);
    }
    close(sd); //소켓기술자를 닫음.
    printf("From Server : %s\n",received); //서버로부터 받은 메세지의 내용을 출력
}
