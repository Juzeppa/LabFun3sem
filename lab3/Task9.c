#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG
#define BUF_SIZE 200

typedef struct Address
{
	char *city;
	char *street;
	int house;
	int apartment;
	int index;
} Address;

typedef struct Mail 
{
	Address adrs;
	float weight;
	int id;
} Mail, *Pmail;

typedef struct Post
{
	Address adrs;
	Pmail mails;
} Post, *Ppost;

Post addmail(Post post, int count, char *citybuf, char *street, int house, int apartment, int index, float weight, int id);
Post* rmmail(Post* post, int id, int count);
Post sortmail(Post post, int count);

int main() 
{ 	
	FILE* fIn;
	Post post;
	post.mails = NULL;
	char citybuf[BUF_SIZE], streetbuf[BUF_SIZE];
	int k, count = 0, house, apartment, index, id;
	float weight;

	if (!(fIn = fopen("9in.txt", "r")))
	{
		printf("Error");
		exit(2);
	}

	fscanf(fIn, "%s %s %d %d %d", citybuf, streetbuf, &house, &apartment, &index);
	post.adrs.city = (char *)malloc(sizeof(char) * strlen(citybuf));
	strcpy(post.adrs.city, citybuf);
	post.adrs.street = (char *)malloc(sizeof(char) * strlen(streetbuf));
	strcpy(post.adrs.street, streetbuf);
	post.adrs.house = house;
	post.adrs.apartment = apartment;
	post.adrs.index = index;

	while (!feof(fIn))
	{
		fscanf(fIn, "%s %s %d %d %d %f %d", citybuf, streetbuf, &house, &apartment, &index, &weight, &id);

		post = addmail(post, count, citybuf, streetbuf, house, apartment, index, weight, id);	
		count++;
	}

	post = sortmail(post, count);

	for (k = 0; k < count; ++k)
		printf("%s %s %d %d %d %.2f %d\n", post.mails[k].adrs.city, post.mails[k].adrs.street, post.mails[k].adrs.house, post.mails[k].adrs.apartment, post.mails[k].adrs.index, post.mails[k].weight, post.mails[k].id);
	
	printf("\nEnter id to delete:\n");

	int dd;

	scanf("%d", &dd);
	
	post = *rmmail(&post, dd, count);
	count--;
	
	for (k = 0; k < count; ++k)
		printf("%s %s %d %d %d %.2f %d\n", post.mails[k].adrs.city, post.mails[k].adrs.street, post.mails[k].adrs.house, post.mails[k].adrs.apartment, post.mails[k].adrs.index, post.mails[k].weight, post.mails[k].id);

	fclose(fIn);
	
	for (k = 0; k < count; ++k)
	{
		free(post.mails[k].adrs.city);
		free(post.mails[k].adrs.street);
	}

	free(post.mails);

	return 0;
}

Post addmail(Post post, int count, char *citybuf, char *streetbuf, int house, int apartment, int index, float weight, int id)
{
	if (!post.mails)
	{
		post.mails = (Pmail)malloc(sizeof(Mail));
		post.mails->adrs.city = (char *)malloc(sizeof(char) * strlen(citybuf));
		strcpy(post.mails->adrs.city, citybuf);
		post.mails->adrs.street = (char *)malloc(sizeof(char) * strlen(streetbuf));
		strcpy(post.mails->adrs.street, streetbuf);
		post.mails->adrs.house = house;
		post.mails->adrs.apartment = apartment;
		post.mails->adrs.index = index;
		post.mails->weight = weight;
		post.mails->id = id;
	}
	else
	{
		post.mails = (Pmail)realloc(post.mails, (count + 1) * sizeof(Mail));
		post.mails[count].adrs.city = (char *)malloc(sizeof(char) * strlen(citybuf));
		strcpy(post.mails[count].adrs.city, citybuf);
		post.mails[count].adrs.street = (char *)malloc(sizeof(char) * strlen(streetbuf));
		strcpy(post.mails[count].adrs.street, streetbuf);
		post.mails[count].adrs.house = house;
		post.mails[count].adrs.apartment = apartment;
		post.mails[count].adrs.index = index;
		post.mails[count].weight = weight;
		post.mails[count].id = id;
	}

	return post;
}

Post* rmmail(Post *post, int id, int count)
{
	int i, j = 0, fl = 0;

	for (j = 0; j < count; j++)
		if (post->mails[j].id == id)
		{
			fl = 1;
			break;
		}

	if (fl == 0)
		return post;

	fl = 0;

	free(post->mails[j].adrs.city);
	free(post->mails[j].adrs.street);

	Post *new;
	new->mails = (Pmail)malloc(sizeof(Mail) * (count - 1));

	for (i = 0; i < count; i++)
		if (i != j)
			new->mails[fl++] = post->mails[i];

	free(post->mails);

	return new;
}

Post sortmail(Post post, int count)
{
	int i, j;
	Mail x;

	for (i = 1; i != count; ++i)
	{
	    x = post.mails[i];
	    j = i;
	    while (j > 0 && post.mails[j - 1].adrs.index > x.adrs.index)
	    {
	        post.mails[j] = post.mails[j - 1];
	        j--;
	    }
	    post.mails[j] = x;
	}

	for (i = 1; i != count; ++i)
	{
	    x = post.mails[i];
	    j = i;
	    while (j > 0 && post.mails[j - 1].adrs.index == x.adrs.index && post.mails[j - 1].id > x.id)
	    {
	        post.mails[j] = post.mails[j - 1];
	        j--;
	    }
	    post.mails[j] = x;
	}

	return post;
}