#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 200

#define DEBUG

typedef struct Student
{
	int id;
	char* name;
	char* surname;
	int group;
} Student, *PStudent;

int main()
{
	/*const char* name = "Ilya";
	const char* surname = "Irbitskiy";
	PStudent pStudent = (PStudent)malloc(sizeof(Student));
	(*pStudent).id = 10;
	pStudent->name = (char*)malloc(sizeof(char) *
		(strlen(name) + 1));
	strcpy(pStudent->name, name);
	pStudent->surname = (char*)malloc(sizeof(char) *
		(strlen(surname) + 1));
	strcpy(pStudent->surname, surname);
	pStudent->group = 210;

	pStudent->id = 15;

	printf("Student: %d %d %s %s\n",
		pStudent->id, pStudent->group,
		pStudent->surname, pStudent->name);

	printf("%d", sizeof(*pStudent));

	free(pStudent->name);
	free(pStudent->surname);
	free(pStudent);*/

	char nameBuf[BUFSIZE], surnameBuf[BUFSIZE];
	int id, group, counter = 0, i;
	FILE* fIn;
	PStudent students = NULL;

	if (!(fIn = fopen("students.txt", "r")))
	{
		printf("input file not found!");
		getchar();
		return -1;
	}

	while (!feof(fIn))
	{
		fscanf(fIn, "%d %s %s %d", &id, nameBuf, surnameBuf, &group);
		counter++;
#ifdef DEBUG
		printf("%d %s %s %d\n", id, nameBuf, surnameBuf, group);
#endif
		if (!students)
		{
			students = (PStudent)malloc(sizeof(Student));
			students->id = id;
			students->group = group;
			students->name = (char*)malloc(sizeof(char) *
				(strlen(nameBuf) + 1));
			strcpy(students->name, nameBuf);
			students->surname = (char*)malloc(sizeof(char) *
				(strlen(surnameBuf) + 1));
			strcpy(students->surname, surnameBuf);
		}
		else
		{
			students = realloc(students, counter * sizeof(Student));
			(students + counter - 1)->id = id;
			(students + counter - 1)->group = group;
			(students + counter - 1)->name = (char*)malloc(sizeof(char) *
				(strlen(nameBuf) + 1));
			strcpy((students + counter - 1)->name, nameBuf);
			(students + counter - 1)->surname = (char*)malloc(sizeof(char) *
				(strlen(surnameBuf) + 1));
			strcpy((students + counter - 1)->surname, surnameBuf);
		}
	}
	fclose(fIn);
	for (i = 0; i < counter; i++)
	{
		free(students[i].name);
		free(students[i].surname);
	}
	free(students);
	return 0;
}