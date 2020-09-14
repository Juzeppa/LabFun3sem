#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define DEBUG
#define BUF_SIZE 100

typedef struct Passenger 
{	
	int number;
	char *airportA;
	char *depart;
	char *airportB;
	char *arrival;
	struct tm arrive;
	struct tm ddepart;
} Passenger, *Ppas;

void printpass(Ppas passengers, int counter);
Ppas deletepass(Ppas passengers, int *counter, int number);
Ppas addpass(int counter, Ppas passengers, int number, int *time1, int *time2, char *arrival, char *depart, char *airportA, char *airportB);
int count(Ppas passengers);

int main(int argc, char *argv[])
{
	int i, counter = 0, number, time1[3], time2[3], cases, fl = 1;
	char airportA[BUF_SIZE], airportB[BUF_SIZE], arrival[BUF_SIZE], depart[BUF_SIZE];

	if(argc < 1)
	{
		printf("PROBLEM!!!\n");
		exit(-1);
	}
	
	FILE *fIn = fopen(argv[1], "r");	
	
	if(fIn == 0)
	{
		printf("There is a problem with file(s)!\n");
		exit(-2);
	}

	Ppas passengers = NULL;

	while (!feof(fIn))
	{
		fscanf(fIn, "%d %s %s %s %s %d:%d:%d %d:%d:%d", &number, airportA, depart, airportB, arrival, &time2[0], &time2[1], &time2[2], &time1[0], &time1[1], &time1[2]);

		if (!passengers) {
			++counter;
			passengers = (Ppas)malloc(sizeof(Passenger));
			passengers->number = number;
			passengers->arrive.tm_hour = time1[0];
			passengers->arrive.tm_min = time1[1];
			passengers->arrive.tm_sec = time1[2];
			passengers->ddepart.tm_hour = time2[0];
			passengers->ddepart.tm_min = time2[1];
			passengers->ddepart.tm_sec = time2[2];
			passengers->airportA = (char*)malloc(sizeof(char) * (strlen(airportA) + 1));
			strcpy(passengers->airportA, airportA);
			passengers->airportB = (char*)malloc(sizeof(char) * (strlen(airportB) + 1));
			strcpy(passengers->airportB, airportB);
			passengers->depart = (char*)malloc(sizeof(char) * (strlen(depart) + 1));
			strcpy(passengers->depart, depart);
			passengers->arrival = (char*)malloc(sizeof(char) * (strlen(arrival) + 1));
			strcpy(passengers->arrival, arrival);
		}
		else
			passengers = addpass(++counter, passengers, number, time1, time2, arrival, depart, airportA, airportB);
	}

	while(fl)
	{
		printf("Choose option: 1 - to add passenger, 2 - to delete, 3 - to print list, 4 - exit:\n");
		scanf("%d", &cases);

		switch(cases)
		{

		case 1:
			printf("Enter the data:\n");
			scanf("%d %s %s %s %s %d:%d:%d %d:%d:%d", &number, airportA, depart, airportB, arrival, &time2[0], &time2[1], &time2[2], &time1[0], &time1[1], &time1[2]);
			passengers = addpass(++counter, passengers, number, time1, time2, arrival, depart, airportA, airportB);
			break;
		
		case 2:
			printf("Enter the needed number:\n");
			scanf("%d", &number);
			passengers = deletepass(passengers, &counter, number);
			break;

		case 3:
			printpass(passengers, counter);
			break;

		case 4:
			fl = 0;
			break;
		}
	}

	for (i = 0; i < counter; ++i)
	{
		free(passengers->airportA);
		free(passengers->airportB);
		free(passengers->arrival);
		free(passengers->depart);
	}

	free(passengers);

	return 0;
}

void printpass(Ppas passengers, int counter)
{
	int i;

	for (i = 0; i < counter; ++i)
		printf("%d %s %s %s %s %d:%d:%d %d:%d:%d\n", passengers[i].number, passengers[i].airportA, passengers[i].depart, passengers[i].airportB, passengers[i].arrival, passengers[i].ddepart.tm_hour, passengers[i].ddepart.tm_min, passengers[i].ddepart.tm_sec, passengers[i].arrive.tm_hour, passengers[i].arrive.tm_min, passengers[i].arrive.tm_sec);
}

Ppas addpass(int counter, Ppas passengers, int number, int *time1, int *time2, char *arrival, char *depart, char *airportA, char *airportB)
{
	passengers = (Ppas)realloc(passengers, counter * sizeof(Passenger));
	(passengers + counter - 1)->number = number;
	(passengers + counter - 1)->arrive.tm_hour = time1[0];
	(passengers + counter - 1)->arrive.tm_min = time1[1];
	(passengers + counter - 1)->arrive.tm_sec = time1[2];
	(passengers + counter - 1)->ddepart.tm_hour = time2[0];
	(passengers + counter - 1)->ddepart.tm_min = time2[0];
	(passengers + counter - 1)->ddepart.tm_sec = time2[0];
	(passengers + counter - 1)->airportA = (char*)
		malloc(sizeof(char) * (strlen(airportA) + 1));
	strcpy((passengers + counter - 1)->airportA, airportA);
	(passengers + counter - 1)->airportB = (char*)
		malloc(sizeof(char) * (strlen(airportB) + 1));
	strcpy((passengers + counter - 1)->airportB, airportB);
	(passengers + counter - 1)->arrival = (char*)
		malloc(sizeof(char) * (strlen(arrival) + 1));
	strcpy((passengers + counter - 1)->arrival, arrival);
	(passengers + counter - 1)->depart = (char*)
		malloc(sizeof(char) * (strlen(depart) + 1));
	strcpy((passengers + counter - 1)->depart, depart);

	return passengers;
}

Ppas deletepass(Ppas passengers, int *counter, int number)
{
	int i = 0, del = -1;

	for (i; i < *counter; ++i)
		if (passengers[i].number == number){
			del = i;
			break;
		}

	if (del == -1)
		return passengers;

	int k = 0;
	Ppas new = (Ppas)malloc(sizeof(Passenger) * (*counter - 1));

	for (i = 0; i < *counter; ++i)
		if (del != i)
			new[k++] = passengers[i];

	free(passengers);
	(*counter)--;
	return new;
}