#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int det(int **mat, int m);
void decomp(int **mat, int **buf, int i, int j, int size); 


int main(int argc, char const *argv[]){
	int size, res, i, j;
	int **A;
	printf("Write n\n");
	scanf("%d", &size);
	if (size <= 0){
		printf("n should be positive\n");
		exit(-1);
	}
	A = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++){
		A[i] = (int*)malloc(size * sizeof(int));
	}
	srand(time(NULL));
	printf("Мatrix А\n");
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			A[i][j] = rand() % 5;
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
	res = det(A, size);
	printf("detA = %d\n", res);
	for (i = 0; i < size; i++)
			free(A[i]);
	free(A);
	return 0;
}


void decomp(int **mat, int **buf, int i, int j, int size) {
	int ai, aj, fl1 = 0, fl2 = 0;
  	
  	for (ai = 0; ai < size - 1; ai++) { 
		if (ai == i) 
			fl1 = 1;
		fl2 = 0;
		for (aj = 0; aj < size - 1; aj++) { 
			if (aj == j) 
				fl2 = 1;
	    	buf[ai][aj] = mat[ai + fl1][aj + fl2];
		}
	}
}


int det(int **mat, int size) {
	int i, k, res;
  	int **buf;
  	res = 0;
  	k = 1;
  	if (size == 1) {
   		res = mat[0][0];
    	return res;
  	}
  	buf = (int**)malloc(size * sizeof(int*));
  	for (i = 0; i < size; i++){
		buf[i] = (int*)malloc(size * sizeof(int));
	}
   	for (i = 0; i < size; i++){
     	decomp(mat, buf, i, 0, size);
      	res = res + k * mat[i][0] * det(buf, size - 1);
      	k = -k;
    }
	for (i = 0; i < size; i++)
		free(buf[i]);
	free(buf);
  	return res;
}