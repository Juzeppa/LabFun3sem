#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 20
//#define DEBUG

typedef struct Student 
{
	char* name;
	char* secname;
	char* surname;
	int group;
	int ex1;
	int ex2;
	int ex3;
	int ex4;
	int ex5;
} Student, *PStudent;

int main() 
{ 	
	FILE *fIn, *fOut;
	PStudent students = NULL;
	char nameBuf[BUFSIZE], surnameBuf[BUFSIZE], secnameBuf[BUFSIZE];
	int i, group, counter = 0, ex1, ex2, ex3, ex4, ex5;
	double average = 0, averagest;

	if (!(fIn = fopen("6in.txt", "r")))
	{
		printf("Error");
		exit(1);
	}

	if (!(fOut = fopen("6out.txt", "w")))
	{
		printf("Error");
		exit(2);
	}

	while (!feof(fIn)) {
		fscanf(fIn, "%s %s %s %d %d %d %d %d %d\n", surnameBuf, nameBuf, secnameBuf, &group, &ex1, &ex2, &ex3, &ex4, &ex5);
		counter++;

	#ifdef DEBUG 
		printf("%s %s %s %d %d %d %d %d %d\n", surnameBuf, nameBuf, secnameBuf, group, ex1, ex2, ex3, ex4, ex5);
	#endif

		if (!students) {
			students = (PStudent)malloc(sizeof(Student));
			students->group = group;
			students->name = (char*)malloc(sizeof(char) * (strlen(nameBuf) + 1));
			strcpy(students->name, nameBuf);
			students->surname = (char*)malloc(sizeof(char) * (strlen(surnameBuf) + 1));
			strcpy(students->surname, surnameBuf);
			students->secname = (char*)malloc(sizeof(char) * (strlen(secnameBuf) + 1));
			strcpy(students->secname, secnameBuf);
			students->ex1 = ex1;
			students->ex2 = ex2;
			students->ex3 = ex3;
			students->ex4 = ex4;
			students->ex5 = ex5;
		}
		else
		{
			students = (PStudent)realloc(students, counter * sizeof(Student));
			(students + counter - 1)->group = group;
			(students + counter - 1)->name = (char*)malloc(sizeof(char) * (strlen(nameBuf) + 1));
			strcpy((students + counter - 1)->name, nameBuf);
			(students + counter - 1)->surname = (char*)malloc(sizeof(char) * (strlen(surnameBuf) + 1));
			strcpy((students + counter - 1)->surname, surnameBuf);
			(students + counter - 1)->secname = (char*)malloc(sizeof(char) * (strlen(secnameBuf) + 1));
			strcpy((students + counter - 1)->secname, secnameBuf);
			(students + counter - 1)->ex1 = ex1;
			(students + counter - 1)->ex2 = ex2;
			(students + counter - 1)->ex3 = ex3;
			(students + counter - 1)->ex4 = ex4;
			(students + counter - 1)->ex5 = ex5;
		}
	}

	fclose(fIn);

	for (i = 0; i < counter; i++)
	{
		averagest = ((students + i)->ex1 + (students + i)->ex2 + (students + i)->ex3 + (students + i)->ex4 + (students + i)->ex5) / 5.;
		fprintf(fOut, "%s %s %s %d %.1f\n", (students + i)->surname, (students + i)->name, (students + i)->secname, (students + i)->group, averagest);
		average += averagest;
	}

	average /= counter;
	printf("%.2f\n", average);

	for (i = 0; i < counter; i++)
	{
		if(average < ((students + i)->ex1 + (students + i)->ex2 + (students + i)->ex3 + (students + i)->ex4 + (students + i)->ex5) / 5.)
			printf("%s %s\n", (students + i)->surname, (students + i)->name);
	}

	for (i = 0; i < counter; i++)
	{	
		free(students[i].name);
		free(students[i].surname);
		free(students[i].secname);
	}

	free(students);
	fclose(fOut);

	return 0;
}