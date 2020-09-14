#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
	int i = 0;
	char str[] = "Arina super dev ochka", *s = str;

	while(*s++)
		if(i++ % 2 != 0)
			*s = toupper(*s);

	printf("%s\n", str);
	return 0;	
}