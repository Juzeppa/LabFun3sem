#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int	Converter(char *ptr, int base){
	int result = 0;
	while (*ptr){
		result = result * base + (isalpha(*ptr) ? toupper(*ptr) - 'A' + 10 : *ptr - '0');
		ptr++;
	}
	return (result);
}

int	Basefinder(char *ptr){
	int result = 0, temp;
	while (*ptr){
		if (isdigit(*ptr))
			temp = *ptr - '0';
		else
			if (isalpha(tolower(*ptr)))
				temp = toupper(*ptr) - 'A' + 10;
			else 
				return (-1);
		if (temp > result)
			result = temp;
		ptr++;
	}
	return (result + 1);
}


int main(int argc, char const *argv[]){
	char number[40], *ptr = number, ch;
	int base;

	FILE *f1, *f2;
	
	if (argc < 2)
	{
		printf("Prolems with files!\n");
		exit(-1);
	}
	
	if((f1 = fopen(argv[1], "r")) == 0 || (f2 = fopen(argv[2], "w")) == 0)
	{
		printf("Can't find any file\n");
		exit (-2);
	}

	while ((ch = fgetc(f1)) != EOF){
		if (!isspace(ch))
			*ptr++ = ch;
		else{
			*ptr = 0;
			if ((base = Basefinder(number)) != -1)
				fprintf(f2, "Number: %s, min count system = %d, in DEC = %d\n", number, base, Converter(number, base));
			ptr = number;
		}
	}

	fclose(f1);
	fclose(f2);
	
	return 0;
}