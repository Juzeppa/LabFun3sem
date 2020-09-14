#include <stdio.h>
#include <stdlib.h>

int main(){
	int x, y;
	scanf("%d %d", &x, &y);
	if(x == 0 || y == 0)
		exit (-1);
	if(x % y == 0)
		printf("Da\n");
	else
		printf("No\n");
}