#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void to2(int a)
{
	if (a)
	{
		to2(a >> 1);
		printf("%d", a & 1);
	}
}

int *k1l(int k, int l)
{
	int i, j = 0, a, res, *arr;
	k = pow(2, k);

	for (i = 0; i < k; ++i)
	{	
		a = i;
		res = 0;
		
		while(a)
		{
			if (a & 1 == 1)
				res++;
			a = a >> 1;
		}

		if (res == l)
		{
			if (j == 0)
			{
				arr = (int *)malloc(sizeof(int));
				*arr = i;
				j++;
			}
			else
			{
				arr = (int *)realloc(arr, sizeof(int) * (j + 1));
				*(arr + j) = i;
				j++;
			}
		}
	}

	return arr;
}

int *cons(double k, double l)
{
	int i, j = 0, a, flag, flaglast, fl = 0, *arr2;
	k = pow(2, k);

	for (i = 0; i < k; ++i)
	{	
		a = i;
		flag = flaglast = fl = 0;
		
		while(a)
		{
			if (a & 1 == 1)
				flag++;
			else
			{
				if (flaglast == l)
				{
					fl = 1;
					break;
				}
				flag = 0;
			}
			if(a == 1 && flaglast + 1 == l)
				fl = 1;
			a = a >> 1;
			flaglast = flag;
		}

		if (fl == 1)
		{
			if (j == 0)
			{
				arr2 = (int *)malloc(sizeof(int));
				*arr2 = i;
				j++;
			}
			else
			{
				arr2 = (int *)realloc(arr2, sizeof(int) * (j + 1));
				*(arr2 + j) = i;
				j++;
			}
		}
	}

	return arr2;
}

int main()
{
	int k, l, j = 0;
	printf("Enter count of bit and ones: ");
	scanf("%d %d", &k, &l);

	int *arr, *arrbeg, *arr2, *arr2beg;
	arr = k1l(k, l);
	arrbeg = arr;

	printf("\nIn %d-bit numbers these have %d 1:\n", k, l);

	while (*arr)
	{
		printf("%d\n", *(arr++));
		//arr++;
	}

	printf("\n");
	free(arrbeg);
	arr2 = cons(k, l);
	arr2beg = arr2;
	j = 0;

	printf("In %d-bit numbers these have %d 1 in a row :\n", k ,l);

	while (*arr2)
	{
		printf("%d\n", *(arr2));
		arr2++;
	}

	free(arr2beg);
	return 0;
}