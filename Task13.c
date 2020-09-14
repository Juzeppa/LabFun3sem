#include <stdio.h>
#include <math.h>
#include <stdarg.h>

typedef struct koor{
	double x;
	double y;
}koor;

int check(koor a, koor b, koor *mnog, int count){
	int i, up = 0, down = 0;

	for(i = 0; i < count; ++i){
		if((a.y - b.y) * mnog[i].x + (b.x - a.x) * mnog[i].y + (a.x * b.y - b.x * a.y) < 0)
			down = 1;
		if((a.y - b.y) * mnog[i].x + (b.x - a.x) * mnog[i].y + (a.x * b.y - b.x * a.y) > 0)
			up = 1;
	}

	return ((up == 0 && down != 0) || (down == 0 && up != 0)) ? 1 : 0;
}

int vipmnog(int count, ...){

	int i, j, flag = 1;
	double mindist;
	va_list args;
	va_start(args, count);
	koor mnog[count];
	
	for(i = 0; i < count; i++)
		mnog[i] = va_arg(args, koor);

	for(i = 0; i < count; ++i){
		koor curkoor = mnog[i], nextkoor;
		
		if(i != count - 1)
			nextkoor = mnog[i + 1];
		else
			nextkoor = mnog[0];

		if(!check(curkoor, nextkoor, mnog, count)){
			flag = 0;
			break;
		}
	}

	va_end(args);
	return flag;
}

int main(){
	//koor koord1 = {1, 2}, koord2 = {2, 4}, koord4 = {4, 3}, koord5 = {2, 1}, koord3 = {2, 2};
	koor koord1 = {1, 1}, koord2 = {1, 4}, koord4 = {5, 3}, koord5 = {4, 2}, koord3 = {3, 9};
	//vipmnog(5, koord1, koord2, koord3, koord4, koord5);
	//koor koord1 = {0, 0}, koord2 = {0, 3}, koord3 = {1, 1}, koord4 = {3, 1};
	//koor koord1 = {-1, -1}, koord2 = {-1, -3}, koord3 = {-4, -4}, koord4 = {-3, -2};
	//koor koord1 = {2, 2}, koord2 = {-2, -2}, koord3 = {-3, -2}, koord4 = {-2, 1};
	int flag = vipmnog(5, koord1, koord2, koord3, koord4, koord5);
	flag ? printf("Vipukliy\n") : printf("Net\n");
	return 0;
}
