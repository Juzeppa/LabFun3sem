#include <stdio.h>

int main(){
	int x, y;
	scanf("%d", &x);
	y = x;
	if(x <= 100 && x != 0){
		printf("%d ", x);
		while(x + y < 100){
			x += y;
			printf("%d ", x);
		}
	}else{
		if(y == 0)
			printf("Vse chisla");
		else 
			printf("No");
	}
	printf("\n");
}