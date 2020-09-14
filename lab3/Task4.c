#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 200
#define STOP (toupper(str[0]) == 'S' && toupper(str[1]) == 'T' && toupper(str[2]) == 'O' && toupper(str[3]) == 'P' && str[4] == '\0')

typedef struct Message
{
	int id;
	char *text;
	int size;
} Message, *Pmess;

int main()
{
	FILE *fill;
	char str[BUF_SIZE];
	int i = 1, id, size, counter = 0, j;
	Message message;
	Pmess mess = NULL;

	if (!(fill = fopen("fill4.txt", "w")))
	{
		printf("Error");
		exit(1);
	}
	
	printf("Please, enter the massages:\n");

	while(1)
	{
		scanf("%s", str);
		if(!STOP)
		{
			message.id = i;
			message.text = (char *)malloc(sizeof(char) * strlen(str));
			strcpy(message.text, str);
			message.size = strlen(str);
			fprintf(fill, "%d %d %s\n", message.id, message.size, message.text);
			i++;
			free(message.text);
		}
		else
			break;
	}

	i--;

	if(i == 0)
		exit(0);

	printf("%d\n", i);

	fclose(fill);
	FILE *empty;

	if (!(empty = fopen("fill4.txt", "r")))
	{
		printf("Error");
		exit(2);
	}

	for (j = 0; j < i; ++j)
	{
		fscanf(empty, "%d %d %s", &id, &size, str);

		if (!mess)
		{
			mess = (Pmess)malloc(sizeof(Message));
			mess->id = id;
			mess->size = size;
			mess->text = (char*)malloc(sizeof(char) * (strlen(str) + 1));
			strcpy(mess->text, str);
		}
		else
		{
			mess = (Pmess)realloc(mess, (j + 1) * sizeof(Message));
			(mess + j)->id = id;
			(mess + j)->size = size;
			(mess + j)->text = (char*)malloc(sizeof(char) * (strlen(str) + 1));
			strcpy((mess + j)->text, str);
		}
	}

	printf("\nYou entered messages(id, size, text of message):\n");

	for (j = 0; j < i; ++j)
		printf("%d %d \"%s\"\n", (mess + j)->id, (mess + j)->size, (mess + j)->text);

	for (j = 0; j < i; ++j)
		free((mess + j)->text);

	free(mess);
	fclose(empty);

	return 0;
}