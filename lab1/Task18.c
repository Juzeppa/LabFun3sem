#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N = 10;

int main(){
	int ar[N], max = 0, min = 0;
	srand(time(NULL));
	ar[0] = rand() % 1000;
	for (int i = 1; i < N; ++i){
		ar[i] = rand() % 1000;
		if(ar[i] > ar[max]) 
			max = i;
		if(ar[i] < ar[min])
			min = i;
		printf("%d ", ar[i]);
	}
	printf("\n");
	int x = ar[min];
	ar[min] = ar[max];
	ar[max] = x;
	for (int i = 0; i < N; ++i)
		printf("%d ", ar[i]);
	printf("\n");
}