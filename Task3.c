#include <stdio.h>

int lenstr(char *str){
	int i = 0;

	while(*str++)
		i++;

	return i;
}

int main(){
	char *str = "Arina super dev ochka";
	printf("%d\n", lenstr(str));

	return 0;
}