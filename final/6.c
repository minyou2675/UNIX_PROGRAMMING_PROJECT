#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 100000000

unsigned int s = 0;
pthread_mutex_t mutex; // 전역변수로 뮤텍스 선언

void *c(void *d)
{ //Critical section thread가 공유하는 영역
    int i;
    for (i = 0; i < N; i++){
    pthread_mutex_lock(&mutex); // 뮤텍스 락 사용
        s++;
    pthread_mutex_unlock(&mutex); // 뮤텍스 락 해제
    }
    return NULL;

}

int main(void){

    pthread_mutex_init(&mutex, NULL); //뮤텍스 초기화

    pthread_t t[2];
    int  r;
    r = pthread_create(&t[0], NULL, c, NULL); //thread 생성
    if( r != 0 ){
        perror("thread create:");
        exit(1);

    }

    r = pthread_create(&t[1], NULL, c, NULL);
    if( r != 0 ){
        perror("thread create:");
        exit(1);
    }
    pthread_join(t[0], NULL); //thread 합치는 작업
    pthread_join(t[1], NULL);
    printf("%u\n", s);
    pthread_mutex_destroy(&mutex); //뮤텍스 제거
    return 0;
}
