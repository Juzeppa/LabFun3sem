#include <stdio.h>
int main(){
	int x, y = 0;
	scanf("%d", &x);
	if(x < 10000000 && x > 1000000){
		while(x > 0){
			y = y * 10 + (x % 10);
			x /= 10;
		}
		for(int i = 0; i < 7; i++){
			printf("%d ", y % 10);
			y /= 10;
		}
	}
	printf("\n");
}