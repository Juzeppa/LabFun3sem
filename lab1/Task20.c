#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <malloc.h>

#define BUFSIZE 80

int main(){
	int countSystem;
	char buf[BUFSIZE] = {0}, *b = buf;
	int isValidNumber;
	int maxValue = 0, currentValue;
	int i;

	printf("Enter count system: ");
	scanf("%d", &countSystem); 
	getchar();

	if (countSystem < 2 || countSystem > 36){
		printf("Invalid count system!");
		getchar();
		return -1;
	}

	while (1){
		printf("Input value in cs %d, stop to break: ", countSystem);
		scanf("%s", buf); 
		getchar();
		if (!strcmp(buf, "stop")){
			break;
		}
		isValidNumber = 1;
		// check for invalid digits
		b = buf;
		while (*b){
			*b = toupper(*b);
			if (!(isdigit(*b) || isalpha(*b)) || (*b - '0' >= countSystem) || (*b - 'A' >= countSystem)){
				printf("Invalid number!\n\n");
				isValidNumber = 0;
				break;
			}
			b++;
			// TODO: check validity
		}
		if (!isValidNumber){
			continue;
		}
		
		b = buf;
		currentValue = 0;
		while (*b){
			currentValue = currentValue * countSystem + (isdigit(*b) ? *b++ - '0' : *b++ - 'A' + 10);
		}
		if (currentValue > maxValue){
			maxValue = currentValue;
		}
	}

	printf("Max value (cs10) = %d\n", maxValue);

	for (countSystem = 9; countSystem <= 36; countSystem += 9){
		b = buf + BUFSIZE - 1;
		*b = 0;
		currentValue = maxValue;
		while (currentValue){
			i = currentValue % countSystem;
			*--b = (i < 10 ? i + '0' : i + 'A' - 10);
			currentValue /= countSystem;
		}
		printf("MaxValue (cs%d) = %s\n", countSystem, b);
	}
	
	return 0;
}