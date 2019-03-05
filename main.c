#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "UI.h"

#define num_elements 14	//numer of elements in dataset
//#define num_elements 5658364

struct movie 
{	
	char id[11];			//imdb given uniqie ID
	char style[20];			//movie, video, tvShort
	char title[100];		//Title of movie
	long key;				//array location/hask key
	int year;				//Year movie was released
	//int run_time;			//length of film (minutes)
	char run_time[15];
	char genre[100];		//top genres
	double average_rating;	//average rating
	int num_votes;			//number of votes for rating
};

struct movie *dummy_item;
struct movie *hash_array[num_elements];

void load_database();
struct movie *delete(struct movie *item);
long hash_function(char title[100]);

int main() 
{

	display_main_menu();
	//Load Dataset
	printf("\n\tLoading dataset ");
	load_database();
	printf("Load Complete\n");	
    

	return 0;
}



void load_database()
{
	FILE *fptr;								//create the file opener
	fptr = fopen("test_data.txt", "r");	//open database 

	int i = 0;
	while (i < num_elements)				//Read until number of items is complete (bad way, but it works)
	{
		struct movie *item = (struct movie*) malloc(sizeof(struct movie));	//create new item with malloc
		if (item == NULL)
		{
			printf("error allocating memory for movie %d\n", i);
		}

		fscanf(fptr,
		 	"%10[^,],	%20[^,],	 %100[^,],	  %d,	  	   %10[^,],		   %lf,					  %d, 				%25s",
			item->id, 	item->style, item->title, &item->year, item->run_time, &item->average_rating, &item->num_votes, item->genre
		);

		long hash_index = item->key;				//get hash_index
		//add item to hash table
		while(hash_array[hash_index] != NULL && hash_array[hash_index]->key != -1)
		{
			//go to next cell
			++hash_index;				
			//wrap around the table
			hash_index %= num_elements;
		}
		hash_array[hash_index] = item;

		printf("\n%s, %s, %s, %d, %s, %f, %d, %s\n",
			item->id, 	item->style, item->title, item->year, item->run_time, item->average_rating, item->num_votes, item->genre
		);
		printf("\n");

		if(i%2 == 0) printf(". ");

		i++;
	}

	return;
}

struct movie *delete(struct movie *item)
{
	//long hash_index = item->key;
	free(item);
	
	
	return NULL;
}

long hash_function(char title[100])
{
	long key = 0;
	//hashign fucntion here
	key = title[100] % num_elements;
	return key;
}