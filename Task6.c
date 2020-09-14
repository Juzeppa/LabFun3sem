#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *konk(char *first, char *second){
	char *res = (char *)malloc(sizeof(char) * (strlen(first) + strlen(second)));
	
	strcpy(res, first);
	strcpy(res + strlen(first), second);
	
	return res;
}

int main(){
	char *a = "Arina super", *b = "dev ochka", *ab = konk(a, b);
	printf("a = %s\nb = %s\na + b = %s\n", a, b, ab);
	free(ab);

	return 0;
}