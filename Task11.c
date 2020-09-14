#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N = 10;

void change(int *min, int *max){
	int a;
	a = *min;
	*min = *max;
	*max = a;
}

int main(){
	int ar[N], max = 0, min = 0;
	srand(time(NULL));
	
	for (int i = 0; i < N; ++i){
		ar[i] = rand() % 1000;
		if(ar[i] > ar[max]) 
			max = i;
		if(ar[i] < ar[min])
			min = i;
		printf("%d ", ar[i]);
	}
	
	printf("\n");
	printf("min = %d, max = %d\n", ar[min], ar[max]);
	change(&ar[min], &ar[max]);

	for (int i = 0; i < N; ++i)
		printf("%d ", ar[i]);

	printf("\n");

	return 0;
}