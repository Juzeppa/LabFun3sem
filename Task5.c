#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
	char *str = "Ar1n@ $u)p9r de/.v 04ka", *str1 = str, *needed = (char *)malloc(sizeof(char) * strlen(str)), *tmp = needed;
	
	while(*str){
		if(isdigit(*str))
			*needed++ = *str;
		str++;
	}

	str = str1;

	while(*str){
		if(isalpha(*str))
			*needed++ = *str;
		str++;
	}

	str = str1;

	while(*str){
		if(!isalnum(*str))
			*needed++ = *str;
		str++;
	}

	printf("%s\n", tmp);
	free(needed);
	return 0;
}