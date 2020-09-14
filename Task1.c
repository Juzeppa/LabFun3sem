#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]){
	FILE *In;
	int arr[64];
	int flag = 1, i = 0, numb;

	if(argc == 0)
		exit(-1);

	if((In = fopen(argv[1], "r")) == NULL){
		printf("Error!!! Can't find input file!\n");
		exit(-2);
	}

	while(!feof(In)){
		fscanf(In, "%d ", (flag %= 2) == 1 ? &arr[i++] : &numb);
		flag++;
	}
	
	for(int j = 0; j < i; j++)
		printf("%d ", arr[j]);

	printf("\n");
	fclose(In);
	return 0;
}