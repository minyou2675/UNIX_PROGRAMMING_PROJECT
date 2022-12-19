#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORTNUM 8000

int main(int argc, char* argv[]){
    char buf[256]; //클라이언트로부터 받을 공간을 저장
    char str[256]; //받은 메세지를 반대로 하여 저장할 공간

    struct sockaddr_in sin, cli; //소켓 정보를 저장할 서버와 클라이언트 용 구조체를 선언
    int sd, ns, clientlen = sizeof(cli);

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ //sd 소켓 기술자에 소켓을 생성하고 실패시 에러처리
        perror("socket");
        exit(1);
    }

    memset((char *)&sin, '\0', sizeof(sin)); //구조체의 길이만큼 구조체의 내용을 초기화
    sin.sin_family = AF_INET; //서버가 사용할 소켓 종류
    sin.sin_port = htons(PORTNUM); //서버가 bind할 주소의 포트넘버
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); //서버가 bind할 주소

    if(bind(sd, (struct sockadrr *)&sin, sizeof(sin))){ //지정한 주소로 bind를 시도하고 실패 시 에러처리
        perror("bind");
        exit(1);
    }
    
    if(listen(sd, 5)){ //클라이언트가 connect를 시도할 때까지 요청을 기다리며, 최대 클라이언트 수는 5개로 할당 실패 시 에러처리
        perror("listen");
        exit(1);
    }
    while(1){ //무한 루프를 설정함으로써 프로세스를 강제 종료할 때까지 서버가 계속 클라이언트 요청을 받을 수 있도록 함
    if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1){ //클라이언트의 요청을 accept 하고 클라이언트 주소 정보는 cli의 소켓 구조체를 이용하여 저장
        perror("accept"); //accept 실패 시 에러처리
        exit(1);
    }
   
    if(recv(ns,buf,sizeof(buf),0) == -1){ //클라이언트가 보내는 요청을 ns 소켓 기술자가 처리하고 메세지 내용은 buf에 저장
        perror("recv");
        exit(1);
    }
    int j = 0;
    for(int i = strlen(buf)-1; i >= 0; i--){ //buf의 길이만큼 반복하여 문자열의 반대로 str에 저장
    	str[j]  = buf[i];
	j++;
    }


    if(send(ns, str, strlen(str)+ 1, 0) == -1){ //저장한 str값은 str 길이에 null 종료 문자를 포함한 사이즈로 지정하고 send로 다시 클라이언트에 보내고 실패 시 에러처리
        perror("send");
        exit(1);
    }
    }
    




}
