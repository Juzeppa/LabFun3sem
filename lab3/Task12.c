#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define STACK_MAX_SIZE 100

#define ISVALID(c) (isdigit(c) || c == '+' || c == '-' || c == '*'\
|| c == '/' || c == '%' || c == '(' || c == ')' || c == '^')

const char* errors[] =
{
	"Input files not found",
	"Stack overflowed",
	"Stack underflowed",
	"Can't create an output file"
};

void error(int errorId);

typedef struct Stack
{
    char data[STACK_MAX_SIZE];
    int size;
} Stack;

void push(Stack *stack, char value)
{
    if (stack->size >= STACK_MAX_SIZE)
    {
        error(2);
    }

    stack->data[stack->size] = value;
    stack->size++;
}

char pop(Stack *stack)
{
    if (stack->size == 0)
    {
        error(3);
    }

    stack->size--;
    return stack->data[stack->size];
}

char peek(Stack *stack)
{
    return stack->data[stack->size - 1];
}

typedef struct Stacki
{
    int data[STACK_MAX_SIZE];
    int size;
} Stacki;

void pushi(Stacki *stack, int value)
{
    if (stack->size >= STACK_MAX_SIZE)
    {
        error(2);
    }

    stack->data[stack->size] = value;
    stack->size++;
}

int popi(Stacki *stack)
{
    if (stack->size == 0)
    {
        error(3);
    }

    stack->size--;
    return stack->data[stack->size];
}

int peeki(Stacki *stack)
{
    return stack->data[stack->size - 1];
}

int processing(char *BUFF, int *fl);
int priority(Stack *stack, char c, char *r);
int closingbr(Stack *stack, char *r);
int calculation(int b, char o, int a, int *fl);
int brackets(char *str);

int main(int argc, char *argv[])
{
	int i, j, k = 0, flag = 0, *fl = &flag;
	FILE *fIn, *fOut;
	char BUFF[STACK_MAX_SIZE];
	int res;

	if (argc < 2)
		error(1);

	for (i = 1; i < argc; ++i)
	{
		if (!(fIn = fopen(argv[i], "r")))
			error(1);

		j = 1;

		printf("File \"%s\":\n", argv[i]);
		char *name = (char *)malloc(sizeof(argv[i]) + 7);
		strcpy(name, argv[i]);
		strcpy(name + strlen(argv[i]) - 4, "mistake.txt");

		if (!(fOut = fopen(name, "w")))
			error(4);

		while ((fgets(BUFF, STACK_MAX_SIZE, fIn)))
		{	
			*fl = 0;
			if (BUFF[strlen(BUFF) - 1] == '\n')
				BUFF[strlen(BUFF) - 1] = '\0';

			if (!brackets(BUFF))
			{
				fprintf(fOut, "number: %d\n%s\n\n", j, BUFF);
			}
			else
			{
				res = processing(BUFF, fl);
				if (*fl == 1)
					printf("%s - Can't divide by 0\n\n", BUFF);
				else if (*fl == -1)
					continue;
				else if (*fl == 3)
					printf("%s - Invalid expression\n\n", BUFF);
				else if (*fl == 2)
					printf("%s - Not enough operations\n\n", BUFF);
				else
					printf("%s = %d\n\n", BUFF, res);
			}
				
			j++;
		}

		fclose(fIn);
		fclose(fOut);
	}

}

void error (int errorId)
{
	printf("Error #%d:\n%s!!1!1\nPress any key to exit...", errorId, errors[errorId - 1]);
	getchar();
	exit(errorId);
}

int brackets(char *str)
{
	int k = 0;

	while(*str)
	{
		if (*str == '(')
			k++;
		else if (*str == ')')
			k--;

		str++;
	}

	if (k == 0)
		return 1;
	else
		return 0;
}

int priority(Stack *stack, char c, char *r)
{
	int i = 0;

	if (c == '(')
	{
		push(stack, c);
	}
	else if (peek(stack) == '(' || stack->size == 0)
	{
		push(stack, c);
	}
	else if (((peek(stack) == '+' || peek(stack) == '-') 
				&& (c == '*' || c == '/' || c == '^' || c == '%'))
			|| ((peek(stack) == '%') && (c == '*' || c == '/' || c == '^'))
		    || ((peek(stack) == '*' || peek(stack) == '/') && (c == '^')))
	{
		push(stack, c);
	}
	else
	{
		while (stack->size != 0 && peek(stack) != '(' && (((c == '+' || c == '-') && peek(stack) == '%')) 
			|| ((c == '+' || c == '-' || c == '%') && (peek(stack) == '/' ||
			peek(stack) == '*')) || ((c == '+' || c == '-' || c == '/' || c == '*' 
			|| c == '%') && peek(stack) == '^') || ((peek(stack) == '+' ||
			peek(stack) == '-') && (c == '+' || c == '-')) || ((peek(stack) == '/'
			|| peek(stack) == '*') && (c == '/' || c == '*')))	
		{
			*r++ = pop(stack);
			i++;
		}

		push(stack, c);
	}

	return i;
}

int closingbr(Stack *stack, char *r)
{
	int i = 0;

	while(peek(stack) != '(')
	{
		i++;
		*r++ = pop(stack);
	}

	pop(stack);

	return i;
}

int calculation(int a, char o, int b, int *fl)
{
	if (o == '*')
		return (a * b);
	if (o == '/' && b == 0)
	{
		*fl = 1;
		return -1;
	}
	else if (o == '/')
		return (a / b);
	if (o == '%')
		return (a % b);
	if (o == '-')
		return (a - b);
	if (o == '+')
		return (a + b);
	if (o == '^')
		return (pow(a, b));	
	return (0);
}

int processing(char *BUFF, int *fl)
{
	Stack stack;
	stack.size = 0;
	Stacki stacki;
	stacki.size = 0;
	char result[STACK_MAX_SIZE * 2], *r = result, *b = BUFF;
	int k, num;

	while (*b)
	{
		if (*b == '\n')
		{
			break;
		}
		else if (isblank(*b))
		{
			b++;
			continue;
		}
		else if (!ISVALID(*b))
		{
			*fl = 3;
			return -1;
		}
		else if (isdigit(*b))
		{
			*r++ = '\'';
			*r++ = *b++;
			while (isdigit(*b))
			{
				*r++ = *b++;
			}
			*r++ = '\'';
		}
		else if (*b == ')')
		{
			r += closingbr(&stack, r);
			b++;
		}
		else 
		{
			r += priority(&stack, *b, r);
			b++;
		}
	}

	if (r - result == 0)
	{
		*fl = -1;
		return -1;
	}

	while (stack.size != 0)
	{
		*r++ = pop(&stack);
	}

	*r = '\0';
	//printf("%s\n", result);

	r = result;

	while (*(r + 1))
	{
		num = 0;
		if (*r == '\'')
		{	
			r++;
			num = *r - '0';
			r++;
			while (*r != '\'')
			{
				num = num * 10 + (*r - '0'); 
				r++;
			}
			r++;
			pushi(&stacki, num);
		}
		else
		{
			k = calculation(popi(&stacki), *r, popi(&stacki), fl);
			if (*fl == 1)
				break;
			pushi(&stacki, k);	
			r++;
		}	
	}

	k = calculation(popi(&stacki), *r, popi(&stacki), fl);
	pushi(&stacki, k);

	if (stacki.size != 1)
		*fl = 2;

	return popi(&stacki);
}