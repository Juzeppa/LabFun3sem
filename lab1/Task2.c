#include <stdio.h>
#include <math.h>

int main(){
	int y = 0, x;
	scanf("%d", &x);
	while(x != 0){
		for(int i = 2; i <= pow(x, 0.5); i++){ 
			if(x % i == 0)
				y++;
			if(y > 0) break;
		}
		if(y > 0) 
			printf("Sostavnoe\n");
		else
			if(x == 1)
				printf("Ni prostoe, Ni sostavnoe\n");
			else
				printf("Prostoe\n");
		scanf("%d", &x);
		y = 0;	
	}
}