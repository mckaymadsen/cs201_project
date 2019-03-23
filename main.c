#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "UI.h"


#define num_elements 14	//numer of elements in dataset
#define max_catalog 50
#define max_search 15
//#define num_elements 5658364

struct movie 
{	
	char id[11];			//imdb given uniqie ID
	char style[20];			//movie, video, tvShort
	char title[100];		//Title of movie
	long location;				//array location/hask key
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
long search_hash(char search_term[50], long search_results[max_search]);

void print_hash_location(int location);

int main() 
{

	display_start();
	
	//Load Dataset
	printf("\n\tLoading dataset ");
	load_database();
	printf("Load Complete\n");	


	char search_term[50];
	
	printf("Enter Search:");
	scanf("%[^\n]*c",search_term);
	//search_term[strlen(search_term)-1] = '\0';

	long search_results[max_search] = {0};
	if (search_hash(search_term, search_results) != -1)
	{    
		int i;
		for (i = 0; i<max_search; i++)
		{
			if (search_results[i] != 0)
			{
				print_hash_location(search_results[i]);
			}
		}
	}
	else
	{
		printf("\nNo Matches\n");
	}
	
	return 0;
}



void load_database()
{
	FILE *fptr;								//create the file opener
	fptr = fopen("test_data.txt", "r");		//open database 

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

		long hash_index = hash_function(item->title);		//get hash_index
		
		//add item to hash table
		while(hash_array[hash_index] != NULL && hash_array[hash_index]->location != -1)
		{
			//go to next cell
			++hash_index;				
			//wrap around the table
			hash_index %= num_elements;
		}
		hash_array[hash_index] = item;
		hash_array[hash_index]->location = hash_index;

		/*printf("\n%s, %s, %s, %d, %s, %f, %d, %s\n",
			item->id, 	item->style, item->title, item->year, item->run_time, item->average_rating, item->num_votes, item->genre
		);
		printf("\n");*/

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

long search_hash(char search_term[50],long search_results[max_search])
{
	int start_index = hash_function(search_term);
	int index = start_index;
	int searched = 0;
	int found = 0;

	while (hash_array[index] != NULL && found != max_search && searched != num_elements-1)
	{
		char * pch = strstr(hash_array[index]->title,search_term);
		if ( pch != NULL) //if martching substirng is found
		{
			found++;
			search_results[searched] = hash_array[index]->location;
		}	

		index++;
		index %= num_elements;

		searched++;
	}

	if (searched == 0)	return -1;

	return 0;
	
	

}

void print_hash_location(int location) //debug
{
	printf("\n%s, %s, %s, %d, %s, %.2f, %d, %s, %ld\n",
		hash_array[location]->id, hash_array[location]->style, hash_array[location]->title, 
		hash_array[location]->year,	hash_array[location]->run_time, hash_array[location]->average_rating, 
		hash_array[location]->num_votes, hash_array[location]->genre, hash_array[location]->location
	);
	printf("\n");
}