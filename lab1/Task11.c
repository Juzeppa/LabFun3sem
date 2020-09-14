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
		exit (1);
	}

	int k = 0, i = 1;
	char c;
	
	while(!feof(f1))
	{
		c = fgetc(f1);
		if (isalpha(c))
			k++;
		else if (c == EOF || c == '\n')
		{
			fprintf(f2, "%d: %d\n", i, k);
			k = 0;
			i++;
		}
	}

	fclose(f1), fclose(f2);
	
	return 0;
}