#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]){
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

	char ch;
	int k = 1;
	
	while ((ch = fgetc(f1)) != EOF)
	{
		if (isspace(ch))
		{
			fprintf(f2, "%c", ch);
			k = (k < 10)? k + 1 : 1;

			while ((ch = fgetc(f1)) != EOF && isspace(ch))
				fprintf(f2, "%c", ch);
		}
		if (k % 10 == 0 && ch != EOF)
			fprintf(f2, "%d", tolower(ch));	
		else if (k % 2 == 0 && ch != EOF)
			fprintf(f2, "%c", tolower(ch));
		else if (k % 5 == 0 && ch != EOF)
			fprintf(f2, "%d", ch);
		else if (ch != EOF)
			fprintf(f2, "%c", ch);
	}

	fclose(f1);
	fclose(f2);
	
	return 0;
}