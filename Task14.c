#include <stdio.h>
#include <math.h>
#define eps 0.0000000000000002

typedef double (*func_ptr)(double);

double dih(func_ptr func, double a, double b) {
	double x;
	while(fabs(a - b) > eps) {
		x = (a + b) / 2.0;
		if (func(b) * func(x) < 0.0) {
			a = x;
		} else {
			b = x;
		}
	}
	return x;
}

double func_1(double x) {
	return 4. - exp(x) - 2.0*pow(x,2);
}

int main(int argc, char const *argv[]){
	double a = 2., b = 3.;
	printf("Уравнение: 4-e^x-2x^2=0, отрезок содержащий корень:[%lf, %lf]\nРезультат: %.20f\n", a, b, dih(func_1, a, b));
	return 0;
}