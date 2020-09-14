#include <stdio.h>
#include <math.h>

double arinasuperdevochkapow(int number, int degr){

	if(number == 0 && degr == 0)
		return NAN;
	
	if(degr == 0)
		return 1.0;
	
	if(number == 0)
		return 0;

	if(degr > 0)
		return number * arinasuperdevochkapow(number, degr - 1);

	if(degr < 0)
		return 1.0 / number * arinasuperdevochkapow(number, degr + 1);
}

int main(){
	printf("%.4f\n", arinasuperdevochkapow(5, -3));

	return 0;
}