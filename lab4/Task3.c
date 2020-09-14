#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_SIZE 20
#define MAX_TEXT 100
#define BUF_MAX 125

#define STOP (toupper(str[0]) == 'S' && toupper(str[1]) == 'T' && toupper(str[2]) == 'O' && toupper(str[3]) == 'P' && (str[4] == '\n' || str[4] == '\0'))

typedef struct Node
{
	char *text;
	int priority;
	struct Node *next;
}Node, *PNode;

PNode Enqueue(int priority, char *text);
PNode Dequeue(PNode list, char *text);
PNode EnqueuePriority(PNode list, int priority, char *text);

int main()
{
	setlocale(LC_ALL, "Rus");
	PNode node, list = NULL;
	char str[MAX_SIZE], text[MAX_TEXT], buff[BUF_MAX], *bufptr, *textptr;
	FILE *fIn;
	int priority;

	while(1)
	{
		printf("Enter name of file or STOP to exit\n");
		scanf("%s", str);
		if(!STOP)
		{
			if (!(fIn = fopen(str, "r")))
			{
				printf("Can't open file %s!!!\n\n", str);
				continue;
			}
			while (!feof(fIn))
			{
				fgets(buff, BUF_MAX, fIn);
				bufptr = buff;
				textptr = text;
				priority = 0;

				while (*bufptr != '=')
					bufptr++;
				bufptr++;
				while (*bufptr != ' ')
					priority = priority * 10 + *bufptr++ - '0';
				//printf("%d ", priority);
				while (*bufptr != '\'')
					bufptr++;
				bufptr++;
				while (*bufptr != '\'')
					*textptr++ = *bufptr++;
				*textptr = '\0';
				//printf("%s\n", text);

				list = EnqueuePriority(list, priority, text);
			}

			printf("File %s successfully read!\n\n", str);
		}
		else
		{
			printf("\n");
			break;
		}
	}

	node = list;

	while (node->next != NULL)
	{
		printf("%s->", node->text);
		node = node->next;
	}

	if (node != NULL)
		printf("%s", node->text);

	node = NULL;

	while (list != NULL)
	{
		free(list->text);
		node = list;
		list = list->next;
		free(node);
	}

	return 0;
}

PNode EnqueuePriority(PNode list, int priority, char *text)
{
	PNode current = list, new;

	if (list != NULL)
	{
		while (current->next != NULL && current->next->priority <= priority)
			current = current->next;

		new = Enqueue(priority, text);

		if (current->next == NULL)
			current->next = new;
		else
		{
			new->next = current->next;
			current->next = new;
		}
		//printf("%s\n", current->next->text);
	}
	else
	{
		list = Enqueue(priority, text);
		//printf("%s\n", list->text);
	}

	return list; 	
}

PNode Enqueue(int priority, char *text)
{
	PNode new = (PNode)malloc(sizeof(Node));
	new->priority = priority;
	new->text = (char *)malloc(strlen(text) * (sizeof(char) + 1));
	strcpy(new->text, text);
	new->next = NULL;

	return new;
}

PNode Dequeue(PNode list, char *text)
{
	PNode current = list;

	while (current->next->next != 0 && strcmp(current->next->text, text) != 0)
		current = current->next;

	current->next = NULL;

	return list;
}