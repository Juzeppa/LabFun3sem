#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 200

typedef struct String 
{
	char* str;
	int length;
} String, *Pst;

String createstr(char* str);
void deletestr(String str);
int comparestr(String str1, String str2);
String concstr(String str1, String str2);
String dublstr(String old);

int main() 
{ 	
	char input[BUF_SIZE];

	printf("Enter first string:\n");
	scanf("%s", input);

	String first = createstr(input);
	printf("First string successfully created and it has length of %d: %s\n\n", first.length, first.str);

	printf("Enter second string:\n");
	scanf("%s", input);

	String second = createstr(input);
	printf("Second string successfully created and it has length of %d: %s\n\n", second.length, second.str);

	printf("String comparison:\n");
	if (!comparestr(first, second))
		printf("Strings match!\n\n");
	else
		printf("Strings don't match!\n\n");

	String third = dublstr(second);
	printf("First string's dublicate(they have different adresses):\n%s %s\n%p %p\n\n", first.str, third.str, first, third);

	String fourth = concstr(first, second);
	printf("Concatenation of first and second: %s\n\n", fourth);

	deletestr(first);
	deletestr(second);
	deletestr(third);
	deletestr(fourth);
	printf("All the strings are successfully deleted. Bye!\n");

	return 0;
}

String createstr(char *str)
{
	String new;
	new.str = (char *)malloc(sizeof(char) * strlen(str));
	strcpy(new.str, str);
	new.length = strlen(new.str);

	return new;
}

void deletestr(String str)
{
	free(str.str);
}

int comparestr(String first, String second)
{
	char *str1 = first.str, *str2 = second.str;
	int i = 0;
    
    while((*str1 != '\0') || (*str2 != '\0'))
    {
        if(*str1 != *str2)
            return 1;
        str1++;
        str2++;
    }
    return 0;

}

String concstr(String first, String second)
{	
	String res;
	res.str = (char *)malloc(sizeof(char) * (strlen(first.str) + strlen(second.str)));
	
	strcpy(res.str, first.str);
	strcpy(res.str + strlen(first.str), second.str);
	
	return res;
}

String dublstr(String old)
{
	String new;
	new.str = (char *)malloc(sizeof(char) * strlen(old.str));
	strcpy(new.str, old.str);
	new.length = old.length;

	return new;
}