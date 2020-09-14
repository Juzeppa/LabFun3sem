#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<ctype.h> 

#define BUF 256 
#define COM 13 
#define AR1 Reg[aAR1 - 'A'] 
#define AR2 Reg[aAR2 - 'A'] 

unsigned short Reg[26] = { 0 };

const char* ErrorArr[BUF] =
{
	"КОМАНДА НЕ НАЙДЕНА", "ВВЕДЕНА НЕВЕРНАЯ КОМАНДА", "КОММЕНТАРИИ ИСКАЖЕНЫ", "НЕВЕРНЫЙ ВВОД"
};

char *ins[COM] = { "IN", "OUT", "NOT", "SETONE", "SETNULL", "NAND", "AND", "XOR", "NOR", "OR", "EQV",  "IMP", "COPY" };
char **cm = ins, aAR1, aAR2;

void Error(int);
void Syntax_error(int);
void IsComment(char ch, FILE* fIn);
void Instruction(int  instruction, char aAR1, char aAR2, FILE* fout);


int main()
{
	int instruction;
	FILE *fIn, *fout;
	char c, buf[BUF], *b = buf;
	if (!(fIn = fopen("fIn.txt", "r")))
		Error(1);
	if (!(fout = fopen("fout.txt", "w")))
		Error(2);
	 while (!feof(fIn))
	{
		c = fgetc(fIn);
		IsComment(c, fIn);
		if ((isalpha(c)) || (c == ','))
			*b++ = toupper(c);
		else if (c == ';')
		{
			*b = NULL;
			b = buf;
			cm = ins;
			int i = 0;
			for (; i < COM; i++)
			if (strstr(buf, *(cm + i)) == buf)
			{
				cm += i;
				break;
			}

			if ((instruction = i) == COM)
			{
				printf("%d\n", i );
				Syntax_error(1);
			}
			if ((instruction >= 0) && (instruction <= 4))
			{
				if (strlen(buf) != (strlen(*cm) + 1))
					Syntax_error(2);
				aAR1 = buf[strlen(*cm)];
			}
			else if ((instruction >= 5) && (instruction <= (COM - 1)))
			{
				if (strlen(buf) != (strlen(*cm) + 3))
					Syntax_error(2);
				if (buf[strlen(*cm)] == ',')
					Syntax_error(2);
				if (buf[strlen(*cm) + 1] != ',')
					Syntax_error(2);
				if (buf[strlen(*cm) + 2] == ',')
					Syntax_error(2);
				aAR1 = buf[strlen(*cm)];
				aAR2 = buf[strlen(*cm) + 2];
			}
			Instruction(instruction, aAR1, aAR2, fout);
		}
		
	}
	fclose(fIn);
	fclose(fout);
	
	return 0;
}

void Instruction(int  instruction, char aAR1, char aAR2, FILE* fout)
{
	char out[BUF] = "\0", *o = out;
	switch (instruction)
	{
		case 0:
			printf("Enter %c value: ", aAR1);
			scanf("%s", out);
			while (*o != 0)
			{
				if (isdigit(*o))
					*o++;
				else
				{
					Syntax_error(4);
				}
			}	
			o = out;
			AR1 = 0;
			while (*o)
			{
				AR1 = AR1 * 10 + (*o++ - '0');
			}
			fprintf(fout, "IN %c = %d\n", aAR1, AR1);
			break;
		case 1:
			fprintf(fout, "OUT %c: ", aAR1);
			fprintf(fout, "%o(8)=", AR1);
			fprintf(fout, "%d(10)=", AR1);
			fprintf(fout, "%X(16)\n", AR1);
			printf("OUT %c: ", aAR1);
			printf("%o(8)=", AR1);
			printf("%d(10)=", AR1);
			printf("%X(16)\n", AR1);
			break;
		case 2:
			AR1 = ~AR1;
			fprintf(fout, "NOT %c\n", aAR1);
			printf("NOT %c\n", aAR1);
			break;
		case 3:
			AR1 = 0;
			fprintf(fout, "SETNULL %c\n", aAR1);
			printf("SETNULL %c\n", aAR1);
			break;
		case 4:
			AR1 = 1;
			fprintf(fout, "SETONE %c\n", aAR1);
			printf("SETONE %c\n", aAR1);
			break;
		case 5:
			AR1 = ~(AR1 & AR2);
			fprintf(fout, "NAND %c,%c\n", aAR1, aAR2);
			printf("NAND %c, %c\n", aAR1, aAR2);
			break;
		case 6:
			AR1 = AR1 & AR2;
			fprintf(fout, "AND %c,%c\n", aAR1, aAR2);
			printf("AND %c, %c\n", aAR1, aAR2);
			break;
		case 7:
			AR1 = AR1 ^ AR2;
			fprintf(fout, "XOR %c,%c\n", aAR1, aAR2);
			printf("XOR %c, %n", aAR1, aAR2);
			break;
		case 8:
			AR1 = ~(AR1 | AR2);
			fprintf(fout, "NOR %c,%c\n", aAR1, aAR2);
			printf("NOR %c, %c\n", aAR1, aAR2);
			break;
		case 9:
			AR1 = AR1 | AR2;
			fprintf(fout, "OR %c,%c\n", aAR1, aAR2);
			printf("OR %c, %c", aAR1, aAR2);
			break;
		case 10:
			AR1 = ~(AR1 ^ AR2);
			fprintf(fout, "EQV %c,%c\n", aAR1, aAR2);
			printf("EQV %c, %c\n", aAR1, aAR2);
			break;
		case 11:
			AR1 = (~AR1) | AR2;
			fprintf(fout, "IMP %c,%c\n", aAR1, aAR2);
			printf("IMP %c, %c\n", aAR1, aAR2);
			break;	
			
		case 12:
			AR1 = AR2;
			fprintf(fout, "COPY %c,%c\n", aAR1, aAR2);
			printf("COPY %c, %c\n", aAR1, aAR2);
			break;
	}
}
	

void IsComment(char ch, FILE* fIn)
{
	int comment = 0;
	if (ch == '{')
		{
			comment = 1;
			while (comment == 1)
			{
				ch = fgetc(fIn);
				if (ch == '}')
					comment = 0;
				if (ch == EOF)
				{
					Syntax_error(3);
				}
			}
		}

}

void Error(int errorcode)
{
	printf("Error(%d)\n", errorcode);
	switch (errorcode)
	{
	case 1:
		printf("ERROR(%d)\n fIn file not found\n", errorcode);
		break;
	case 2:
		printf("ERROR(%d)\n fout file not found\n", errorcode);
		break;
	}
	exit(errorcode);
}

void Syntax_error(int code)
{
	printf("Fatal Error(%d)\n", code);
	switch (code)
	{
	case 1:
		printf("%s\n", ErrorArr[0]);
		break;
	case 2:
		printf("%s\n", ErrorArr[1]);
		break;
	case 3:
		printf("%s\n", ErrorArr[2]);
		break;
	case 4:
		printf("%s\n", ErrorArr[3]);
		break;
	}
	exit(code);
}