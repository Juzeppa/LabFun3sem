#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define HASHSIZE 128

typedef struct Node
{
	char word[HASHSIZE];
	int val;
	struct Node *next;
}Node, *PNode;

int getmod(char *str);
void totable(PNode *table, char *str, int i);
void toprint(PNode *table, char *str);

void exit_(int number, char *str)
{
    switch(number)
    {
        case -1:
        		printf("Can't define string by string\n");
                exit(number);
        case -2:
        		printf("%s already was defined!\n", str);
                exit(number);
        case -3:
        		printf("Can't open input file\n");
        		exit(number);
    }
}

int main(int argc, char* argv[])
{
	FILE* fIn;
	int i, d;
	char str[HASHSIZE], c, str2[HASHSIZE], *str3;
	PNode table[HASHSIZE];

	for (i = 0; i < HASHSIZE; ++i)
		table[i] = NULL;

	if (!(fIn = fopen(argv[1], "r")))
		exit_(-3, "s");

	printf("Result:\n");

	while (!feof(fIn))
	{
		d = 0;
		fscanf(fIn, "%s", str);
		if (!strcmp(str, "#define"))
		{
			fscanf(fIn, "%s %s", str, str2);
			fgetc(fIn);
			str3 = str2;
			while (*str3)
				if (!isdigit(*str3++))
					exit_(-1, str);
			d = atoi(str2);
			totable(table, str, d);
		}
		else
		{
			toprint(table, str);
			while (!feof(fIn))
			{
				fscanf(fIn, "%s", str);
				toprint(table, str);
			}
		}
	}

	printf("\n");

	fclose(fIn); 
	return 0;
}

int getmod(char *str)
{
	char *b = str;
	unsigned long long currentValue = 0;

	while (*b)
	{
		currentValue = currentValue * 64 + (isdigit(*b) ? *b++ - '0' : isupper(*b) ? *b++ - 'A' + 10 : *b++ - 'A' + 4);
	}

	return currentValue % HASHSIZE;
}

void totable(PNode *table, char *str, int d)
{
	int i = getmod(str);

	if (!table[i])
	{
		*(table + i) = (PNode)malloc(sizeof(PNode));
		strcpy(table[i]->word, str);;
		table[i]->val = d;
		table[i]->next = NULL;
	}
	else
	{
		PNode empty = table[i];
		if (!strcmp(str, empty->word))
				exit_(-2, str);

		while (empty->next != NULL)
		{
			if (!strcmp(str, empty->word))
				exit_(-2, str);
			empty = empty->next;
		}

		empty = (PNode)malloc(sizeof(PNode));
		strcpy(empty->word, str);
		empty->val = d;
		empty->next = NULL;
	}
}

void toprint(PNode *table, char *str)
{
	int i = getmod(str);

	if (!table[i])
		printf("%s ", str);
	else if (table[i])
	{
		PNode end = table[i];

		while (end)
		{
			if (!strcmp(str, end->word))
				break;
			end = end->next;
		}

		if (end)
			printf("%d ", end->val);
		else
			printf("%s ", str);
	}
}