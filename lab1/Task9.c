#include <stdio.h>

int main(){
	int x, y = 0, a = 1;
	scanf("%d", &x);
	while(a <= x){
		y = y + a;
		a++;
	}
	printf("%d\n", y);
}