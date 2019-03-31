#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "movie.h"
#include "hash.h"
#include "catalog.h"
#include "UI.h"





Catalog *newCatalog(unsigned int max_catalog)
{
    Catalog *catalog = (Catalog*)malloc(sizeof(Catalog));

    catalog->capacity = max_catalog;
    catalog->size = 0;

    catalog->movie = newArray(max_catalog);
    for(int i = 0; i < max_catalog; i++)
    {
            catalog->movie[i] = initalize();
    }

    catalog->size = max_catalog;
    return catalog;
}

/*
 * This function returns a 1 when a catalog is created sucessfully and a -1 if it failed.
 * The user is prompted to enter a string, which becomes the file name. ".txt" is added
 * to the end to make it a text file.
 */
int create_catalog()
{
	char name[55] = "";
	printf("\tEnter the name of the catalog you'd like to create. Filename must be within 3 and 150 \n");
	printf("\talphanumeric characters for ease of use. Do not include the filextension. \n\tName: ");

	char buf[1024];
	fgets(buf, 1024, stdin);
  	sscanf(buf, "%s", name);

	if (strlen(name) > 150)
	{
		printf("\n\tName not within the given paramters. Try again");
		return-1;
	}
	strcat(name,".txt");
    
	FILE *fptr;
	fptr = fopen(name, "w"); 
  	if (fptr != NULL)
  	{
		fclose(fptr);
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
 */
int open_catalog(int load_flag, Catalog *current_catalog)
{
	char name[55] = "\0";
	int not_valid_file = 0;
	while(not_valid_file == 0)
	{
		printf("\n\tEnter the name of the catalog you'd like to read. \n");
		printf("\n\tType \"Return\" to stop. \n");
		printf("\tInclude the file extension: ");

		char buf[1024];
		fgets(buf, 1024, stdin);
		sscanf(buf, "%s", name);

		if (strcmp(name,"Return")== 0) 
		{
			return 0;
		}	
		else
		{
			not_valid_file = 1;
		}		
	}

	FILE *fptr;
	fptr = fopen(name, "r"); 
	if (fptr == NULL)
	{
		printf("\n\tFileread Error. Please try again with the correct title.");
	}
	else
	{
		printf("\n\tOpened sucessfully!\n");
		not_valid_file = 1;
		fclose(fptr);
		load_catalog(name, current_catalog);
		if (!load_flag)	display_catalog(current_catalog);			
		return 1;
	}	
	return 0;
}

/*
 * This function loads a text file containing movie data into the current catalog. Is uses the
 * same process as the load_database() function
 */
void load_catalog(char filename[55], Catalog *current_catalog)
{
	FILE *fptr;
	fptr = fopen(filename, "r"); 
	if (fptr == NULL)
	{
			printf("\nFileread Error. Please try again with the correct title.");
	}

	char buff[1024];
	int num_movies = 0;

	fgets(buff, 1024, fptr);
	num_movies = atoi(buff);
	current_catalog->size = num_movies;
	if (num_movies == 0) 
	{
		printf("\n\tCatalog blank or corrupted, please load a different one.\n");
	} 

	for (int i = 0; i < num_movies; i++)
	{
		Movie *item;
        item = newMovie(fptr,1, buff);

		current_catalog->movie[i] = item;
	}
	for (int j = num_movies; j < current_catalog->capacity; j++)
	{
		current_catalog->movie[j] = initalize();
	}
	
	printf("\n\tCatalog Loaded Sucessfully\n");
}

/*
 * This fucntion displays the values in the current catalog.
 */
void display_catalog(Catalog *current_catalog)
{
	printf("\n\tCatalog: \n\tTitle (first 30 characters)   \t\tYear\tRun Time\tRating\tVotes\tGenre\t\tDistribution\n");
	for (int i = 0; i < current_catalog->capacity; i++)
	{
		if (current_catalog->size == 0)
		{
			printf("\n\tCatalog Empty, add movies through the main screen\n");
			return;
		}

		else if (current_catalog->movie[i]->distribution > 0)
		{	
			printf("\n\t%d.", i+1);	
			printf(" %-30.30s\t%d\t%s\t\t%.2f\t%d\t%s",
				current_catalog->movie[i]->title, 
				current_catalog->movie[i]->year,	current_catalog->movie[i]->run_time, current_catalog->movie[i]->average_rating, 
				current_catalog->movie[i]->num_votes, current_catalog->movie[i]->genre 
			);
			if (current_catalog->movie[i]->distribution == 1) printf("\t%s"," BluRay");
			if (current_catalog->movie[i]->distribution == 2) printf("\t%s"," DVD");
			if (current_catalog->movie[i]->distribution == 3) printf("\t%s"," Digital");
		}
	}
	printf("\n");
}


/* 
 * This function goes tot he given location and shifts the items in the array down by 1 to delete
 * the selected movie.
 */
void delete_movie(Catalog *current_catalog)
{
	display_catalog(current_catalog);
	int movie_choice = remove_cat_display(current_catalog->size);
	
	if (movie_choice == -1)
	{
		printf("\n\tMovie removal unsucessful, please try again\n");
		return;
	}

	for (int i = movie_choice-1; i < current_catalog->capacity; i++)
	{
		if (i < current_catalog->capacity-1)
			current_catalog->movie[i] = current_catalog->movie[i+1]; 
	}

	printf("\n\tMovie Sucessfully Removed\n");
	return;
}

/*
 * This function writes the current catalog to a given filename.
 */
void save_catalog(Catalog *current_catalog)
{
	char filename[55];
	char buf[1024];
	char *trash = "bogus";

	printf("\n\tEnter the filename you want to save the current catalog to. If you\n ");
	printf("\tenter an existing filename, it will be overwritten. Make sure you have loaded\n");
	printf("\tthe catalog before adding movies to it.\n\n\tEnter filename: ");
	fgets(buf, 1024, stdin);
	sscanf(buf, "%s", filename);

	FILE *fptr;
	fptr = fopen(filename, "w"); 
	if (fptr == NULL)
	{
			printf("\nFileread Error. Please try again.");
			return; 
	}

	fprintf(fptr, "%d", current_catalog->size);
	for (int i = 0; i < current_catalog->capacity; i++)
	{
		if (current_catalog->movie[i]->distribution > 0)
		{
			/*char *p = strrchr(current_catalog[i].movie->genre, '\n');  	//removes trailing newline from mainfile
			if (p != NULL) *p = '\0';*/

			fprintf(fptr,	"\n%s\t%s\t%s\t%d\t%s\t%lf\t%d\t%d\t%s",
			current_catalog->movie[i]->id, current_catalog->movie[i]->title,	trash, current_catalog->movie[i]->year, 
			current_catalog->movie[i]->run_time, current_catalog->movie[i]->average_rating, current_catalog->movie[i]->num_votes, 
			current_catalog->movie[i]->distribution,	current_catalog->movie[i]->genre 
			
			);
		}
	}
	fclose(fptr);

	return;
}

/*
 * This function removes an existing file (catalog).
 */
int remove_catalog()
{
	char buf[1024];
	char filename[155];
	printf("\n\tWelcome to remove a catalog menu. Enter the filename of the catalog\n");
	printf("\tyou'd like to remove: ");

	fgets(buf, 1024, stdin);
	sscanf(buf, "%s", filename);

	int status = remove(filename);
	return status;
}