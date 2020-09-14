#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUF_SIZE 256

int main(int argc, char *argv[]){
	char str[BUF_SIZE], *strptr, *bufptr;
	
	if (argc < 2)
	{
		printf("Prolems with files!\n");
		exit(-1);
	}

	FILE *f1, *f2;
	
	if((f1 = fopen(argv[1], "r")) == 0 || (f2 = fopen(argv[2], "w")) == 0)
	{
		printf("Can't find any file\n");
		exit (-2);
	}

	while(fgets(str, BUF_SIZE, f1)){
		strptr = str;
		bufptr = strptr;
		while (!isspace(*strptr))
			strptr++;
		*strptr = '\0';
		while (*++strptr != '\n')
			fprintf(f2, "%c", *strptr);
		fprintf(f2, " %s\n", bufptr);
	}

	fclose(f1), fclose(f2);
	char c;
	f2 = fopen(argv[2], "r");
	f1 = fopen(argv[1], "w");
	
	while ((c = fgetc(f2)) != EOF)
		fprintf(f1, "%c", c);
	
	return 0;
}

/*aaaaa bbbb cccc
aaaaaa bbbbbbbb ccccccccc
aa bbb ccccccccccc
*/
