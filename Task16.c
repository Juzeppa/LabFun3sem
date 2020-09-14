#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

char *add0(char *number, int len){
	
	int i;

	if(strlen(number) > len){
		char *d = (char *)(malloc(sizeof(char) * strlen(number) + 1));
		strcpy(d + 1, number);
		d[0] = '0';
		return d;
	} else {
		char *d = (char *)(malloc(sizeof(char) * len + 1));
		for(i = 0; i < len - strlen(number) + 1; ++i)
			d[i] = '0';
		strcpy(d + len - strlen(number) + 1, number);
		return d;
	}
}

char *rm0(char *withzero){

	if(withzero[0] != '0')
		return withzero;

	char *withoutzero = (char*)(malloc(sizeof(char) * strlen(withzero)));
	strcpy(withoutzero, withzero + 1);
	return(withoutzero);
}

char *add(char *firstnum, char *secondnum, int countsystem){
	
	int k = strlen(firstnum);
	firstnum = add0(firstnum, strlen(secondnum));
	secondnum = add0(secondnum, k);

	int i;
	k = 0;
	char *res = (char *)malloc((sizeof(char)) * strlen(firstnum));
	res = res + strlen(res);	

	for (i = 0; i < strlen(firstnum); ++i){
		char num1 = firstnum[strlen(firstnum) - i - 1];
		char num2 = secondnum[strlen(secondnum) - i - 1];
		int result = k + (isdigit(num1) ? num1 - '0' : toupper(num1) - 'A' + 10) + (isdigit(num2) ? num2 - '0' : toupper(num2) - 'A' + 10);
		*(--res) = ((result % countsystem > 9) ? (result % countsystem) - 10 + 'A' : (result % countsystem) + '0');
		k = result / countsystem;
	}
	
	return (rm0(res));	
}

char *sum(int count, int countsystem, ...){
	
	int i;
	char *s = "0", *curnumber;
	va_list args;
	va_start(args, countsystem);
	
	for(i = 0; i < count; i++){
		curnumber = va_arg(args, char *);
		s = add(s, curnumber, countsystem);
	}

	va_end(args);
	return rm0(s);
}

int main(){
	//scanf("%s", sum());
	printf("'%s'\n", sum(10, 16, "-", "2", "3", "4", "5", "6", "7", "8", "9", "A"));
}