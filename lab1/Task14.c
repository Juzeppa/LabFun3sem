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

	char c;
	
	while((c = fgetc(f1)) != EOF)
		if (!(isdigit(c)))
			fprintf(f2, "%d", c);
		else 
			fprintf(f2, "%c", c);
	
	fclose(f1);
	fclose(f2);
	f2 = fopen(argv[2], "r");
	f1 = fopen(argv[1], "w");
	
	while ((c = fgetc(f2)) != EOF)
		fprintf(f1, "%c", c);
	
	fclose(f1);
	fclose(f2);
	
	return 0;
}