#include <stdio.h>
#include <math.h>

int main(){
	int x;
	scanf("%d", &x);
	for (int i = 1; i < 11; i++){
		printf("%d: ", i);
		for (int j = 0; j <= x; j++)
			printf("%.0f ", pow(i, j));
		printf("\n");
	}
}