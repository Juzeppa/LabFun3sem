#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <stdarg.h>

/*char* reverse(char* str) {
	char tmp;
	char * s1, * s2;
	s1 = str;//указатель на начало строки
	s2 = str + (strlen(str) - 1);//указатель на конец строки
	
	for(int i = 0; i < strlen(str) / 2; ++i) {
	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;
	s1++;//положение указателя
	s2--;
	}

	return(str);
}
*/
/*int *prefix(char * str){
	int k;
	int *p = (int *)malloc(sizeof(int) * strlen(str));

	p[0] = 0;
	
	for(int i = 1; i < strlen(str); ++i){
		k = p[i - 1];
		while(k > 0 && str[i] != str[k])
			k = p[k - 1];
		if(str[i] == str[k])
				k++;
		p[i] = k;
	}
	printf("\n");
	return p;
}

int *kmp(int *p, int tl, int pl){
	int *ans = (int *)malloc(sizeof(int) * tl);
	int k = 0;
	for(int i = 0; i < tl; ++i)
		if(p[pl + i + 1] == pl)
			ans[k++] = i;

	return ans;
}*/

int main(int argc, char *argv[]){
	FILE *In = fopen(argv[1], "r"), *In1 = In;
	/*char *withoutzero = "ABC", *a = "ABCDE";
	char *withzero = (char*)(malloc(sizeof(char) * strlen(withoutzero) + 1));
	strcpy(withzero + 1, withoutzero);
	withzero[0] = '0'; 
	printf("%s %s %s\n", withzero, withoutzero, a);*/

	/*char *b = "ABC", *a = "ABCDE";
	int i;
	//printf("%s %s %d %d\n", a, b, strlen(a), strlen(b));
	if(strlen(a) > strlen(b)){
		char *c = (char *)(malloc(sizeof(char) * strlen(a) + 1));
		strcpy(c + strlen(a) - strlen(b) + 1, b);
		for(int i = 0; i < strlen(a) - strlen(b) + 1; i++)
			c[i] = '0';
		b = c;
		char *d = (char *)(malloc(sizeof(char) * strlen(a) + 1));
		strcpy(d + 1, a);
		d[0] = '0';
		a = d;
	} else {
		char *c = (char *)(malloc(sizeof(char) * strlen(b) + 1));
		strcpy(c + strlen(b) - strlen(a) + 1, a);
		for(int i = 0; i < strlen(b) - strlen(a) + 1; i++)
			c[i] = '0';
		a = c;
		char *d = (char *)(malloc(sizeof(char) * strlen(a) + 1));
		strcpy(d + 1, b);
		d[0] = '0';
		b = d;
	}*/
/*char *a = "ABC", b = 2;
	int i;

	if(strlen(a) > b){
		char *d = (char *)(malloc(sizeof(char) * strlen(a) + 1));
		strcpy(d + 1, a);
		d[0] = '0';
		printf("%s\n", d);;
	} else {
		char *d = (char *)(malloc(sizeof(char) * b + 1));
		for(i = 0; i < b - strlen(a) + 1; ++i)
			d[i] = '0';
		strcpy(d + b - strlen(a) + 1, a);
		printf("%s\n", d);;
	}

	printf("%c\n", a[0]);

	char *p = a + strlen(a) - 1;
	char g = a[strlen(a) - 0 - 1];
	printf("%s %c\n", p, g);
	--p;
	printf("%c\n", *(--p));*/
	/*int k = 0;
	char *firstnum = "0E", *secondnum = "0E", countsystem = 16;
	char *res = (char *)malloc((sizeof(char)) * strlen(firstnum)), *resend = res + strlen(res);
	printf("%d %d\n", strlen(resend), strlen(res));	
	for (int i = 0; i < strlen(firstnum); ++i){
		char num1 = firstnum[strlen(firstnum) - i - 1];
		char num2 = secondnum[strlen(secondnum) - i - 1];
		//printf("%c %c\n", num1, num2);
		int result = k + (isdigit(num1) ? num1 - '0' : toupper(num1) - 'A' + 10) + (isdigit(num2) ? num2 - '0' : toupper(num2) - 'A' + 10);
		//printf("%d\n", result);
		*(--resend) = ((result % countsystem > 9) ? (result % countsystem) - 10 + 'A' : (result % countsystem) + '0');
		//printf("%c\n", *resend);
		k = result / countsystem;
	}
	printf("%s\n", resend);*/
	/*char *ttr(int i, ...){
		va_list args;
		va_start(args, i);
		char *c = va_arg(args, char *);
		return c;
	}
	
	char *s = ttr(1, "ttr");
	printf("%s\n", s);
	return 0;*/
	/*int a;
	scanf("%d", &a);
	int arr[a];
	arr[0] = 6854;
	printf("%d\n", arr[0]);
	*arr = (int *)realloc(arr, 2);*/
	/*char *str = "nort#nortnortnortnortnortrrt";
	int* pp;
	pp = prefix(str);
	printf("%d\n", strlen(str));
	for(int i = 0; i < strlen(str); ++i)
		printf("%d", pp[i]); 
	printf("\n");

	int *s = kmp(pp, 23, 4);
	for(int i = 0; i < 23; ++i)
		printf("%d", s[i]); 
	printf("\n");*/
	
	/*char str[512];
	scanf("%s", str);
	printf("%s\n", reverse(str));*/

	/*int a = 1, *ptr;
	*ptr = a;
	printf("%d %d %d %d\n", a, *ptr, &a, ptr);*/

	char c, c2, *cc = &c, *cc2 = &c2;
	*cc = fgetc(In);
	printf("%c\n", *cc);
	*cc = fgetc(In);
	printf("%c\n", *cc);
	*cc2 = fgetc(In1);
	printf("%c\n", *cc2);

	char *str = "ASD";
	str++;
	str++;
	str++;
	printf("%d %s\n", strlen(str), str);

	
	char *p;
	p = (char *) malloc(17);
	if(!p) {
	printf("Allocation error.");
	exit (1);
	}
	strcpy(p, "This is 16 chars");
	p = (char *) realloc (p,18);
	if(!p) {
	printf("Allocation error.");
	exit (1);
	}
	strcat (p, ".");
	printf(p);
	free(p);

	return 0;
}