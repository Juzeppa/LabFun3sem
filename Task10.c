#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int counter(char *ch, FILE *In);

int main(int argc, char *argv[]){
	

	if(argc < 2){
		printf("PROBLEM!!!\n");
		exit(-1);
	}
	FILE *In = fopen(argv[1], "r"), *Out = fopen(argv[2], "w");	
	if(In == 0 || Out == 0){
		printf("There is a problem with file(s)!\n");
		exit(-2);
	}

	int k, i = 0;
	char c, *ch = &c;
	
	while(!feof(In))
		fprintf(Out, "%d: %d\n", ++i, counter(ch, In));

	fclose(In), fclose(Out);
	
	return 0;
}

int counter(char *ch, FILE *In){
	int k = 0;
	*ch = fgetc(In);
	
	while(*ch != '\n' && *ch != EOF){
		if(isalpha(*ch))
			k++;
		*ch = fgetc(In);
	}

	return k;
}
