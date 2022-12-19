#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int compare_strings(const void *a, const void *b){
    const char* string_a = *(const char**)a;
    const char* string_b = *(const char**)b;
    return strcmp(string_a,string_b);
}

int r_compare_strings(const void *a, const void *b){
    const char* string_a = *(const char**)a;
    const char* string_b = *(const char**)b;
    return -strcmp(string_a,string_b);
}


int main(int argc, char* argv[]){

if(argc < 2){
    perror("argument");
    exit(1);
}

printf("Queue Order:\n");
for(int i = 1; i < argc; i++){
    printf("%s ",argv[i]);
}
puts("");

printf("Stack Order:\n");
for(int i = argc; i >1; i--){
    printf("%s ",argv[i]);
}
puts("");

printf("Alphabetical Order:");
qsort(&argv[1], argc-1, sizeof(char *),compare_strings);
for(int i = 1; i < argc; i++){
    printf("%s ", argv[i]);
}
puts("");
printf("Reverse Alphabetical Order:");
qsort(&argv[1], argc-1, sizeof(char *),r_compare_strings);
for(int i = 1 ; i < argc; i++){
    printf("%s ", argv[i]); 
}
puts("");


}