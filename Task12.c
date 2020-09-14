#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>

int findss(char *substr, FILE *In){
	char *sstr = substr, c = fgetc(In), *ch = &c, *str = (char *)malloc(sizeof(char));
	int i = 0, flag = 0, finish = 0, start = 1, k = 1, fk = 1;
	if(*ch == EOF)
		exit(-1);

	while(*ch != EOF && *ch != '\n'){
		strcat(str, ch);
		str = (char *) realloc(str, strlen(str) + 1);
		*ch = fgetc(In);
	}

	char *firstalpha = str;

	//printf("%s %s\n", str, sstr);

	while(*str){
		if(*str == *substr){
			if(firstalpha == str)
				start = 0;
			else
				start = 1;
			firstalpha = str;
			fk = k;
		}
		if(*str == *sstr){
			flag = 1;
			if(flag && strlen(sstr) == 1 && *str + 1 == *sstr + 1){
				finish = 1;
				break;
			}
			sstr++;
		} else {
			flag = 0;
			sstr = substr;
			if(start){
				str = firstalpha;
				continue;
				printf("%d\n", k);
				k = fk;
				printf("%d\n", k);
			}
		}
		str++;
		k++;
	}

	if(finish == 1)
		return k - strlen(substr);
	else
		return -1;
}

void search(char *substr, int count, ...){
	va_list args;
	va_start(args, count);
	int n = 0, i, k;

	for(i = 0; i < count; ++i){
		FILE *In = fopen(va_arg(args, char *), "r");

		while(!feof(In)){
			n++;
			k = findss(substr, In);
			//printf("%d\n", k);
			if(k > -1)
				printf("In %d file on %d line starting with %d\n", i + 1, n, k);
		}
			if(k < 0)
				printf("In %d file couldn't find any coincidences\n", i);
	}
}

int main(){
	search("arina", 1, "12a.txt"/*, "12ar.txt", "12ari.txt"/*, "12arin.txt*/);
	//findss("ariarinarina", "arina");
}