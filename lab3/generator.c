#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define fname 6in.txt
#define N 10
#define mark rand() % 4 + 2

int main()
{
	FILE *fout = fopen("6in.txt", "w");
	int i, max = N + 1;
	srand(time(NULL));

	for (i = 1; i < max; ++i)
	{
		fprintf(fout, "Surname%d Name%d Secondname%d %d %d %d %d %d %d\n", i, i, i, rand() % 11 + 201, mark, mark, mark, mark, mark);
	}
}