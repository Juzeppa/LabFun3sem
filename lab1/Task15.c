#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

int main(int argc, char *argv[]){
	FILE *f1, *f2, *f3;
	char ch1[100];

	if (argc < 3)
	{
		printf("Prolems with files!\n");
		exit(-1);
	}
	
	if((f1 = fopen(argv[1], "r")) == 0 || (f2 = fopen(argv[2], "r")) == 0 || (f3 = fopen(argv[3], "w")) == 0)
	{
		printf("Can't find any file\n");
		exit (-2);
	}

	while (!feof(f1) || !feof(f2))
	{
		if (fgets(ch1, MAX, f1))
			fprintf(f3, "%s\n", ch1);

		if (fgets(ch1, MAX, f2))
			fprintf(f3, "%s\n", ch1);
	}
	
	fprintf(f3, "\n");

	fclose(f1);
	fclose(f2);
	fclose(f3);
	
	return 0;
}