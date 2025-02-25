#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 100

typedef struct Employee
{
	int id;
	char *name;
	char *surname;
	int salary;
} Employee, *Pemp;

void search(Pemp employees, int n, FILE *fOut);

int main(int argc, char *argv[])
{
	printf("%d\n", 1 << 1);
	if(argc < 2)
	{
		printf("PROBLEM!!!\n");
		exit(-1);
	}
	
	FILE *fIn = fopen(argv[1], "r"), *fOut = fopen(argv[2], "w");	
	
	if(fIn == 0 || fOut == 0)
	{
		printf("There is a problem with file(s)!\n");
		exit(-2);
	}

	Pemp employees = NULL, endemployees;
	char nameBuf[BUF_SIZE], surnameBuf[BUF_SIZE];
	int id, salary, counter = 0;

	while (!feof(fIn)) 
	{
		fscanf(fIn, "%d %s %s %d", &id, nameBuf, surnameBuf, &salary);
		counter++;

		if (!employees) {
			employees = (Pemp)malloc(sizeof(Employee));
			employees->id = id;
			employees->salary = salary;
			employees->name = (char*)malloc(sizeof(char) * (strlen(nameBuf) + 1));
			strcpy(employees->name, nameBuf);
			employees->surname = (char*)malloc(sizeof(char) * (strlen(surnameBuf) + 1));
			strcpy(employees->surname, surnameBuf);
		}
		else
		{
			employees = (Pemp)realloc(employees, counter * sizeof(Employee));
			(employees + counter - 1)->id = id;
			(employees + counter - 1)->salary = salary;
			(employees + counter - 1)->name = (char*)
				malloc(sizeof(char) * (strlen(nameBuf) + 1));
			strcpy((employees + counter - 1)->name, nameBuf);
			(employees + counter - 1)->surname = (char*)
				malloc(sizeof(char) * (strlen(surnameBuf) + 1));
			strcpy((employees + counter - 1)->surname, surnameBuf);
		}
	}

	fclose(fIn);
	search(employees, counter - 1, fOut);
	printf("Successfully sorted!\n");

	return 0;
}

void search(Pemp employees, int n, FILE *fOut)
{
	int i, j;
	Pemp tmp[n];
	Pemp x = (Pemp)malloc(sizeof(Pemp));

	for(i = 0; i < n; ++i)
		tmp[i] = employees + i;

	for (i = 0; i < n; ++i)
	{
	    x = tmp[i];
	    j = i;
	    while (j > 0 && tmp[j - 1]->salary > x->salary)
	    {
	        tmp[j] = tmp[j - 1];
	        j--;
	    }
	    tmp[j] = x;
	}

	printf("Sorted by salary:\n");
	for(i = 0; i < n; ++i)
		printf("%d %s %s %d\n", tmp[i]->id, tmp[i]->name, tmp[i]->surname, tmp[i]->salary);

}