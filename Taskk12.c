#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#define SIZE 128

void find(char *substr, int count, ...);
size_t check(char* substr, char* filename);

int main(){
    char str[SIZE];
    printf("Введите подстроку: ");
    scanf("%s", str);
    find(str, 3, "12a.txt", "12ar.txt", "12ari.txt");
    return 0;
}


void find(char* substr, int count, ...){
    size_t flag = 0, j;
    char *file_name;
    va_list args;
    va_start(args, count);
    for (j = 0; j < count; j++){
        file_name = va_arg(args, char*);
        flag = check(substr, file_name);
        if (!flag)
        {
            printf("File %s has substring %s\n", file_name, substr);
        }
        else
        {
            printf("File %s has no substring %s\n", file_name, substr);
        }
    }
    va_end(args);
}


size_t check(char* substr, char* file_name){
    size_t size = strlen(substr), flag = 0, i;
    char *sub;
	char c;
    sub = (char*)malloc(size * sizeof(char));    
    FILE *fIn = fopen(file_name, "r");
    for (i = 0; i < size; i++){
            *sub++ = fgetc(fIn);
        }
        sub -= size;
        while(!feof(fIn)){
            flag = strcmp(sub, substr);
            if (!flag){
                return flag;
            }
            for (i = 1; i < size; i++){
                *(sub + i - 1) = *(sub + i);
            }
            *(sub + i - 1) = fgetc(fIn);
        }	
    free(sub);
    fclose(fIn);
    return flag;

}