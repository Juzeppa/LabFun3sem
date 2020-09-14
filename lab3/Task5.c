#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 200
//#define DEBUG

typedef struct Student 
{
	int id;
	char* name;
	char* surname;
	int group;
} Student, *PStudent;

void searchid(PStudent students, PStudent end, int x);
void searchgr(PStudent students, PStudent end, int x);
void searchname(PStudent students, PStudent end, char *name);
void searchsurname(PStudent students, PStudent end, char *surname);

int main(int argc, char *argv[]) 
{ 	
	FILE* fIn;
	PStudent students = NULL, endstudents;
	char nameBuf[BUFSIZE], surnameBuf[BUFSIZE];
	int id, group, counter = 0, cases, x, end = 0;

	if (argc < 1)
		exit(1);

	if (!(fIn = fopen("5in.txt", "r")))
	{
		printf("Error");
		exit(2);
	}

	while (!feof(fIn))
	{
		fscanf(fIn, "%d %s %s %d", &id, nameBuf, surnameBuf, &group);
		counter++;

	#ifdef DEBUG 
		printf("%d %s %s %d\n", id, nameBuf, surnameBuf, group);
	#endif

		if (!students) {
			students = (PStudent)malloc(sizeof(Student));
			students->id = id;
			students->group = group;
			students->name = (char*)malloc(sizeof(char) * (strlen(nameBuf) + 1));
			strcpy(students->name, nameBuf);
			students->surname = (char*)malloc(sizeof(char) * (strlen(surnameBuf) + 1));
			strcpy(students->surname, surnameBuf);
		}
		else
		{
			students = (PStudent)realloc(students, counter * sizeof(Student));
			(students + counter - 1)->id = id;
			(students + counter - 1)->group = group;
			(students + counter - 1)->name = (char*)
				malloc(sizeof(char) * (strlen(nameBuf) + 1));
			strcpy((students + counter - 1)->name, nameBuf);
			(students + counter - 1)->surname = (char*)
				malloc(sizeof(char) * (strlen(surnameBuf) + 1));
			strcpy((students + counter - 1)->surname, surnameBuf);
		}
	}

	endstudents = students + counter - 1; 
	fclose(fIn);

	printf("Please, choose the search: by id(1),\n by surname(2),\n by name(3)\n or by group(4)\n and (5) to close the program: ");
	
	while(scanf("%d", &cases))
	{
		switch(cases)
		{	
			case 1:
				printf("Enter id: ");
				scanf("%d", &x);
				searchid(students, endstudents, x);
				break;

			case 2:
				printf("Enter surname: ");
				scanf("%s", surnameBuf);
				searchsurname(students, endstudents, surnameBuf);
				break;

			case 3:
				printf("Enter name: ");
				scanf("%s", nameBuf);
				searchname(students, endstudents, nameBuf);
				break;

			case 4:
				printf("Enter group: ");
				scanf("%d", &x);
				searchgr(students, endstudents, x);
				break;

			case 5:
				end = 1;
				break;
		}
		if(end)
			break;
		printf("\nChoose the search: ");
	}

	for (int i = 0; i < counter; i++)
	{	
		free(students[i].name);
		free(students[i].surname);
	}

	free(students);

	return 0;
}

void searchid(PStudent students, PStudent end, int x)
{
	PStudent tmpstd = students;
	int k = 0;

	while(tmpstd != end)
	{
		if(tmpstd->id == x){
			printf("%d %s %s %d\n", tmpstd->id, tmpstd->name, tmpstd->surname, tmpstd->group);
			k++;
			break;
		}
		tmpstd++;
	}

	if(k == 0)
		printf("Can't find id %d\n", x);
}

void searchgr(PStudent students, PStudent end, int x)
{
	PStudent tmpstd = students;
	int k = 0;

	while(tmpstd != end)
	{
		if(tmpstd->group == x)
		{
			printf("%d %s %s %d\n", tmpstd->id, tmpstd->name, tmpstd->surname, tmpstd->group);
			k++;
		}
		tmpstd++;
	}

	if(k == 0)
		printf("Can't find any students from %d group\n", x);
}

void searchname(PStudent students, PStudent end, char *name)
{
	PStudent tmpstd = students;
	int k = 0;
	
	while(tmpstd != end)
	{
		if(!strcmp(tmpstd->name,name))
		{
			printf("%d %s %s %d\n", tmpstd->id, tmpstd->name, tmpstd->surname, tmpstd->group);
			k++;
			break;
		}
		tmpstd++;
	}

	if(k == 0)
		printf("Can't find %s\n", name);
}

void searchsurname(PStudent students, PStudent end, char *surname)
{
	PStudent tmpstd = students;
	int k = 0;

	while(tmpstd != end)
	{
		if(!strcmp(tmpstd->surname,surname))
		{
			printf("%d %s %s %d\n", tmpstd->id, tmpstd->name, tmpstd->surname, tmpstd->group);
			k++;
			break;
		}
		tmpstd++;
	}


	if(k == 0)
		printf("Can't find %s\n", surname);
}