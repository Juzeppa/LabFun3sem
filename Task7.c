#include <stdio.h>
#include <math.h>
#include <stdarg.h>

double srgeom(int count, ...){

	int i;
	double mult = 1, new;
	va_list args;
	va_start(args, count);
	
	for(i = 0; i < count; i++){
		new = va_arg(args, double);
		mult *= new;
	}

	va_end(args);
	return pow(mult, 1.0 / count);
}

int main(){
	printf("%.2f\n", srgeom(3, 2.0, 4.0, 8.0));

	return 0;
}