#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//bcgwbcgw	

const char* errors[] =
{
	"Input file not found",
	"Instruction is too long",
	"Invalid instruction",
	"Command not found",
	"Can't put anything from empty boat",
	"Can't take any object, boat is full",
	"This object on the other river's side",
	"Wolf eats goat. You lose!!!",
	"Goat eats cabbage. You lose!!!"
};

const char* com[5] =
{
	"move", "put", "takecabbage", "takegoat", "takewolf"
}, **cm = com;

void error(int errorId);
void refresh (int *map, int *boat, int com);

int main(int argc, char *argv[])
{
	FILE* fIn;
	char c, buf[11], *b = buf;
	int mmap = 15, *map = &mmap, bboat = 0, *boat = &bboat;

	if (!(fIn = fopen(argv[1], "r")))
	{
		error(1);
	}

	while ((c = fgetc(fIn)) != EOF)
	{
		//c = fgetc(fIn);

		if (!isalpha(c) && !isspace(c) && c != ';')
		{
			error(3);
		}
		else if (isalpha(c) || isspace(c))
		{
			if (isalpha(c))
			{
				*b++ = c;
			}
		}
		else if (c == ';')
		{
			*b = '\0';
			b = buf;
			for (cm = com; cm - com < 5; cm++)
			{
				if (strstr(buf, *cm) == buf)
				{
					break;
				}
			}
			if (cm - com == 5)
			{
				error(4);
			}

			refresh(map, boat, cm - com);
		}
	}

	if (*map == 240 || *map == 232)
		printf("You win!!!\n");
	else 
		refresh(map, boat, -1);

	return 0;
}

void refresh (int *map, int *boat, int com)
{
	if ((*map & 1 && *map & 2 && *map & 128) || (*map & 16 && *map & 32 && *map & 8)) 
		error(8);

	if ((*map & 2 && *map & 4 && *map & 128) || (*map & 32 && *map & 64 && *map & 8))
		error(9);

	switch(com)
	{
		case 0:
			if (*map & 128)
			{
				*map &= 127;
				*map |= 8;
			}
			else
			{
				*map &= 247;
				*map |= 128;
			}
			break;

		case 1:
			if (*boat != 0)
			{
				*map |= *boat;
				*boat = 0;
				break;
			}
			else
			{
				error(5);
			}

		case 2:
			if (*boat != 0)
			{
				error(6);
			}
			else if (*map & 4 && *map & 8)
			{
				*boat = 1 << 6;
				*map &= 251;
			}
			else if (*map & 64 && *map & 128)
			{
				*boat = 1 << 2;
				*map &= 191;
			}
			else
			{
				error(7);
			}

			break;

		case 3:
			if (*boat != 0)
			{
				error(6);
			}
			else if (*map & 2 && *map & 8)
			{
				*boat = 1 << 5;
				*map &= 253;
			}
			else if (*map & 32 && *map & 128)
			{
				*boat = 1 << 1;
				*map &= 223;
			}
			else
			{
				error(7);
			}

			break;

		case 4:
			if (*boat != 0)
			{
				error(6);
			}
			else if (*map & 1 && *map & 8)
			{
				*boat = 1 << 4;
				*map &= 254;
			}
			else if (*map & 16 && *map & 128)
			{
				*boat = 1;
				*map &= 239;
			}
			else
			{
				error(7);
			}

			break;
	}
}

void error (int errorId)
{
	printf("Error #%d:\n%s!!1!1\nPress any key to exit...", errorId, errors[errorId - 1]);
	getchar();
	exit(errorId);
}