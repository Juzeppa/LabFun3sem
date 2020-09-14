#include <stdio.h>
#include <stdlib.h>

int main(){
	int m1 = 2, n1 = 3, m2 = 3, n2 = 3, i, j, k;
	int arr1[2][3] = {1, 2, 3, 4, 5, 6};
	int arr2[3][3] = {7, 8, 9, 1, 2, 3, 4, 5, 6};

	for(i = 0; i < m1; ++i){
		for(j = 0; j < n1; ++j)
			printf("%d ", arr1[i][j]);
		printf("\n");
	}

	printf("\n");

	for(i = 0; i < m2; ++i){
		for(j = 0; j < n2; ++j)
			printf("%d ", arr2[i][j]);
		printf("\n");
	}

	printf("\n\n");

	if(n1 == m2)
		for(i = 0; i < m1; ++i){
			for(j = 0; j < n2; ++j){
				int sum = 0;
				for(k = 0; k < n1; ++k)
					sum += arr1[i][k] * arr2[k][j];
				printf("%d ", sum);
			}
			printf("\n");
		}
	else
		printf("Can't multiply these matrices\n");

	return 0;
}