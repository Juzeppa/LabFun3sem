#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reversestr(char *str){
	char *res = (char *)malloc(sizeof(char) * (strlen(str) + 1)), *ress = res, *strend = str + strlen(str) - 1;
	
	for(int i = 0; i < strlen(str); i++){
		*ress++ = *strend--;
	}
	*++ress = '\0';

	return res;
}

int main(){
	char *str = "Arina super dev ochka Daniil Bakh Nastya", *res = reversestr(str);
	
	printf("%s\n%s\n", str, res);
	free(res);

	return 0;
}