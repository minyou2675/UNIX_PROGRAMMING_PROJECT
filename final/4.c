#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int compare_strings(const void *a, const void *b){
    const char* string_a = *(const char**)a;
    const char* string_b = *(const char**)b;
    return strcmp(string_a,string_b); //strcmp로 문자의 값을 비교하여 정수를 리턴하고 알파벳
}

int r_compare_strings(const void *a, const void *b){
    const char* string_a = *(const char**)a; //a 문자열의 주소 첫번째(첫단어)를 저장
    const char* string_b = *(const char**)b; //b 문자열 주소 첫번째(첫단어)를 저장
    return -strcmp(string_a,string_b); // compare_strings 값의 부호를 반대로 하여 알파벳의 역순으로 
}


int main(int argc, char* argv[]){

if(argc < 2){ //들어온 인자가 없을 시 에러처리
    perror("argument");
    exit(1);
}

printf("Queue Order:\n"); //선입선출의 방식으로 출력
for(int i = 1; i < argc; i++){
    printf("%s ",argv[i]);
}
puts("\n");

printf("Stack Order:\n");//후입선출의 방식으로 출력
for(int i = argc-1; i >0; i--){
    printf("%s ",argv[i]);
}
puts("\n");

printf("Alphabetical Order:\n"); 
qsort(&argv[1], argc-1, sizeof(char *),compare_strings);//정렬은 qsort를 이용하며, 비교하는 함수는 알파벳순으로 비교할 수 있도록 지정한 함수를 사용
for(int i = 1; i < argc; i++){
    printf("%s ", argv[i]);
}
puts("\n");
printf("Reverse Alphabetical Order:\n"); 
qsort(&argv[1], argc-1, sizeof(char *),r_compare_strings);//정렬은 qsort를 이용하며, 비교하는 함수는 알파벳의 역순으로 비교하도록 지정한 함수를 사용
for(int i = 1 ; i < argc; i++){
    printf("%s ", argv[i]); 
}
puts("\n");


}
