#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 8000

int main(int argc char* argv){

    int sd;
    char buf[256];
    struct sockaddr_in sin;

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ //소켓 생성하고 실패 시 에러처리
        perror("socket");
        exit(1);
    }

    memset((char *)&sin, '\0', sizeof(sin)); 
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sd, (struct sockaddr *)&sin, sizeof(sin)) == -1){
        perror("connect");
        exit(1);
    }
    if(recv(sd, buf, sizeof(buf), 0) == -1){
        perror("recv");
        exit(1);
    }
    close(sd);
    printf("From Server : %s\n",buf);
}
