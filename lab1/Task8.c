#include <stdio.h>

int main(){
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	a *= a, b *= b, c *= c;
	if((a + b == c || a + c == b || a + c == b) && a != 0 && b != 0 && c != 0)
		printf("Yes\n");
	else
		printf("No\n");
}