#include <stdio.h>
#include <string.h>
#include <math.h>

#define BUF_SIZE 32

char allnum[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int mask(int n)
{
	int i, mask = 0;

	for (i = 0; i < n; ++i)
	{
		mask = mask << 1;
		mask |= 1;
	}

	return mask;
}

void check(int num, int n, char *res)
{

	void to2n(int num, int n, char *res)
	{
		if (num)
		{
			to2n(num >> n, n, res + 1);
			*res = allnum[num & mask(n)];
		}
		else
			*res = '\0';
	}

	if (num == 0)
	{
		*res = '0';
		*++res = '\0';
	}
	else
		to2n(num, n, res);
}

char* reverse(char* str) {
	char tmp;
	char *s1, *s2;
	s1 = str;
	s2 = str + (strlen(str) - 1);
	
	for(int i = 0; i < strlen(str) / 2; ++i) {
		tmp = *s2;
		*s2 = *s1;
		*s1 = tmp;
		s1++;
		s2--;
	}

	return(str);
}

int main()
{
	int number, pw2;
	char ress[BUF_SIZE], *res = ress;
	printf("Please, enter number and power of 2 or 5051 61600 to exit:\n");

	while(1)
	{	
		scanf("%d %d", &number, &pw2);
		if (number == 5051 && pw2 == 61600)
			break;

		if (pw2 > 0 && pw2 < 6)
		{
			check(number, pw2, res);
			printf("%s\n\n", reverse(ress));
		}
		else
		{
			printf("ERROR!!! Enter 0 > power < 6\n\n");
		}
	}

	return 0;
}