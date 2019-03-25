/*  Filename:       main.c
 *  Author:         McKay Madsen
 *  Date:           3/15/19
 *  Version:        2.0
 *  Description:
 *    TODO
 *  Notes:
 * 		Requires: UI.c
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "UI.h"


#define num_elements 36	//numer of elements in dataset
#define max_search 15
//#define num_elements 5658364 (all)
//#define num_elements 511709 (movies)

struct movie 
{	
	char id[11];			//imdb given uniqie ID
	//char style[20];			//movie, video, tvShort
	char title[150];		//Title of movie
	long location;				//array location/hash key
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

int create_catalog();
int load_catalog();

void print_hash_location(int location);

int main() 
{
	int max_catalog = 50;
	display_start();
	
	printf("\n\tLoading dataset ");
	load_database();
	printf("Load Complete\n");	

	int main_menu_choice = 0;
	int update_catalog_choice = 0;
	int create_catalog_choice = 0;
	int read_catalog_choice = 0;
	//int exit_flag = 0;

	while(main_menu_choice != -1)	//looop until exit xuit
	{
		main_menu_display();
		main_menu_choice = main_menu_input();
		if (main_menu_choice == -1) break;
		
		printf("\nuser choice: %d\n", main_menu_choice); //debug

		//while(exit_flag != 1)
		//{
			switch(main_menu_choice)
			{
				case 4 :	//REMOVE -- TODO
					//TODO
					break;
				case 3 :	//UPDATE -- TODO
					update_catalog_display();
					update_catalog_choice = update_catalog_input();
					
					update_catalog_choice = 0;		//reset choice
					break;
				case 2 :	//LOAD -- TODO
					read_catalog_display(max_catalog);
					read_catalog_choice = read_catalog_input();
					if (read_catalog_choice == 2) break;
					else if(read_catalog_choice == 1) load_catalog();

					read_catalog_choice = 0;		//reset choice
					break;
				case 1 :	//CREATE -- TODO
					create_catalog_display(max_catalog);
					create_catalog_choice = create_catalog_input();
				printf("\n%d",create_catalog_choice);//debug
					if (create_catalog_choice == 2) break;
					else if (create_catalog() == 1) printf("\n\tCatalog created sucessfully!\n");//goto main menu somehow
					
					create_catalog_choice = 0;	//reset choice
					break;
				case 0 :
					printf("Yikes, nohting happened in main_menu_input");
					break;
				default : 
				printf("somthing went wrong");
					//exit_flag = 1;
					break;
			}

		//}
		//search debug
		/*
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
		//end search debug
		*/
	}	
	return 0;
}



void load_database()
{
	FILE *fptr;								//create the file opener
	fptr = fopen("test_data2.txt", "r");		//open database 
	char trash[25];

	int i = 0;
	while (i < num_elements)				//Read until number of items is complete (bad way, but it works)
	{
		struct movie *item = (struct movie*) malloc(sizeof(struct movie));	//create new item with malloc
		if (item == NULL)
		{
			printf("error allocating memory for movie %d\n", i);
		}

		fscanf(fptr,
		 	"%10[^\t]\t	%100[^\t]\t %20[^\t]\t	 	  %d\t	  	   %10[^\t]\t		   %lf\t					  %d\t 				%25s",
			item->id, item->title,	trash, &item->year, item->run_time, &item->average_rating, &item->num_votes, item->genre
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

		/*printf("\n%s,  %s, %d, %s, %f, %d, %s\n",
			item->id, 	item->title, item->year, item->run_time, item->average_rating, item->num_votes, item->genre
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

/*
 * This function returns a 1 when a catalog is created sucessfully and a -1 if it failed.
 * The user is prompted to enter a string, which becomes the file name. ".txt" is added
 * to the end to make it a text file.
 * 
 * TODO: 	add in error checking for filesize name
 * 				add in error handinling for failed file
 */

int create_catalog()
{
	char name[55] = "";
	printf("\tEnter the name of the catalog you'd like to create. It can be a max of 50 \n");
	printf("\talphanumeric characters. Do not include the file extension: ");

	char buf[BUFSIZ];
	fgets(buf, BUFSIZ, stdin);
    sscanf(buf, "%s", name);
	//ADD in error checking for size

	strcat(name,".txt");
    
	FILE *fptr;
	fptr = fopen(name, "w"); 
  if (fptr != NULL)
  {
		return 1;
  }
	else
	{
		return -1;
	}
}

/*
 * This function loads a catalog when given a filename (string). If not string is given
 * i.e. string == NULL, it prompts the user for the filename.
 * 
 * TODO:	add in load from file
 * 				add in prompt use for name
 * 				add in display catalog 
 */
int load_catalog()
{
	//get catalog name and display catalog
	printf("\nWORKING\n");
	return 0;
}

/*
 * This function prints out the data at a given hash location in the table.
 */
void print_hash_location(int location) 
{
	printf("\n%s, %s, %d, %s, %.2f, %d, %s, %ld\n",
		hash_array[location]->id, hash_array[location]->title, 
		hash_array[location]->year,	hash_array[location]->run_time, hash_array[location]->average_rating, 
		hash_array[location]->num_votes, hash_array[location]->genre, hash_array[location]->location
	);
	printf("\n");
}