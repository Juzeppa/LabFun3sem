#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define eps 0.000000000000000000000000001

int main(){
	double a, b, c;
	scanf("%le %le %le", &a, &b, &c);

	if(a < eps){
		printf("Can't solve this!\n");
		exit(-1);
	}
	
	double d = pow(b, 2) - 4 * a * c;
	
	if(d < 0)
		printf("D < 0, I can't solve this\n");
	else if(d > 0){
		printf("x1 = %.2f\n", (-b + pow(d, 0.5)) / (2 * a));
		printf("x2 = %.2f\n", ((-1 * b) - pow(d, 0.5)) / (2 * a));
	} else
		printf("x = %f\n", (-1 * b) / (2 * a));
	
	return 0;
}