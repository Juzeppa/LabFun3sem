#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

double val_at_point(double x, int count, ...){
	va_list args;
	va_start(args, count);
	count++;
	double sum = 0;
	int i;

	for(i = 0; i < count; ++i)
		sum = sum * x + va_arg(args, double);
	
	return sum;
}

int main(){
	printf("%.2lf\n", val_at_point(2, 2, 1.0, 1.0, 1.0));

	return 0;
}

//x^2+x+1=(x + 1)x + 1=(((0x + 1)x + 1)x +1)