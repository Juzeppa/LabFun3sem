#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define N 10

int main(){
	srand(time(NULL));
	int A[N], B[N], C[N];
	char D[N] = {0};
	printf("1: ");
	
	for (int i = 0; i < N; ++i){
		A[i] = rand() % 19;
		printf("%d ", A[i]);
	}

	printf("\n2: ");
	
	for (int i = 0; i < N; ++i){
		B[i] = rand() % 18;
		printf("%d ", B[i]);
	}

	int x = 0, y = 0;
	printf("\nThe nearest number from (1) to (2):\n   ");
	
	for (int i = 0; i < N; ++i){
		x = INT_MAX; 
		for (int j = 0; j < N; ++j){
			if(abs(A[i] - B[j]) < x && D[j] != '+'){
				x = abs(A[i] - B[j]);
				y = j;
			}
		}
		printf("%d ", B[y]);
		A[i] += B[y];
		//D[y] = '+';
	}

	printf("\n\n   ");
	
	for (int i = 0; i < N; ++i)
		printf("%d ", A[i]);
	printf("\n");
	
	return 0;
}