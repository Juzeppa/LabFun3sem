#include <stdio.h>
#include <ctype.h>
#include <math.h>

const int N = 14;

int main(){
	int in[] = {1, 2, 1, 2, 7, 5, 6, 7, 4, 5, 0, 0, -1, -1};
	int out[N], i = 0, j = 0, flag = 1, end = 0, nul = 0;

	for(i = 0; i < N; ++i){
		out[i] = 0;
		printf("%d ", in[i]);
	}

	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j)
			if(in[i] == out[j]){
				flag = 0;
				break;
			}
		if(in[i] == 0 && nul++ == 0) 
			flag++;
		if(flag++ != 0)
			out[end++] = in[i];
	}

	printf("\n");

	for(i = 0; i < end; ++i){
		printf("%d ", out[i]);
	}

	printf("\n");
	return 0;
}