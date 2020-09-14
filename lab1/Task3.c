#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
	char c;
	FILE *f1, *f2;
	f1 = fopen("File.txt", "r");
	f2 = fopen("File1.txt", "w");
	if(f1 == 0){
		printf("1Error\n");
		exit(1);
	}
	while((c = fgetc(f1)) != EOF)
		if (!(isdigit(c)))
			fprintf(f2, "%c", c);
	fclose(f1);
	fclose(f2);
	f2 = fopen("File1.txt", "r");
	f1 = fopen("File.txt", "w");
	while ((c = fgetc(f2)) != EOF)
		fprintf(f1, "%c", c);
	fclose(f1);
	fclose(f2);
	return 0;
}