#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char const *argv[]){
	FILE *In;
	int arr[128];
	int flag = 1, i = 0, numb;

	if(argc < 1){
		printf("Error! Put an iput file!!!\n");
		exit(-1);
	}

	if ((In = fopen(argv[1], "r")) == NULL){
		printf("Error!!! Can't find input file!\n");
		exit(-2);
	}

	while (!feof(In)){
		fscanf(In, "%d", &numb);
		if (numb % 2 == 0){
			arr[i++] = numb;
		} 
	}

	for (int j = 0; j < i; j++)
		printf("%d ", arr[j]);

	printf("\n");
	fclose(In);
	return 0;
}