#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "movie.h"

/*
 *	Contains the constructors for the movie
 */


Movie **newArray(unsigned int size)
{
    Movie **movie = malloc(sizeof(Movie*) * size);
    return movie;
}

/*
 * This function sets the given struct to NULL values.
 */
Movie *initalize(void)
{
	Movie *item = (Movie *)malloc(sizeof(Movie));
	//item->title = malloc(sizeof(item->title));
	
	strcpy(item->title, "\0");
	item->year = 0;
	strcpy(item->run_time,"\0");
	item->num_votes = 0;
	item->average_rating = 0.00;
	strcpy(item->genre,"\0");
	item->distribution = 0;

	return item;
}

Movie *newMovie(FILE *fptr, int cat_flag, char buff[1024])
{
    //char buff[1024];

    Movie *item = malloc(sizeof(Movie));	//create new item with malloc
	if (item == NULL)
	{
		printf("error allocating memory for movie\n");
	}
		
    if (cat_flag)
    {
        fgets(buff, 1024, fptr);
		char *token = strtok(buff,"\t");
		strcpy(item->id, token);
		token = strtok(NULL,"\t");
		strcpy(item->title, token);
		token = strtok(NULL,"\t");				//trash the movie part of the read
		token = strtok(NULL,"\t");
		item->year = atoi(token);
		token = strtok(NULL,"\t");
		strcpy(item->run_time,token);
		token = strtok(NULL,"\t");
		item->average_rating = atof(token);
		token = strtok(NULL,"\t");
		item->num_votes =  atoi(token);
		token = strtok(NULL,"\t");
		item->distribution = atoi(token);
		token = strtok(NULL,"\r\n");
		strcpy(item->genre, token);

        return item;
    }
    else
    {
        //fgets(buff, 1024, fptr);
        char *token = strtok(buff,"\t");
        strcpy(item->id, token);
        token = strtok(NULL,"\t");
        strcpy(item->title, token);
        token = strtok(NULL,"\t");					//trash this line as its the "movie" tag
        token = strtok(NULL,"\t");
        item->year = atoi(token);
        token = strtok(NULL,"\t");
        strcpy(item->run_time,token);
        token = strtok(NULL,"\t");
        item->average_rating = atof(token);
        token = strtok(NULL,"\t");
        item->num_votes =  atoi(token);
        token = strtok(NULL,"\r");
        strcpy(item->genre, token);

        return item;
    }
    
}

/*
 * This function prints out the data at a given hash location in the table.
 */
void print_movie(Movie *movie) 
{
		//printf("%s\t%d\t%s\t%.2f\t%d\t%s",
		printf("\t%-30.30s\t%d\t%s\t\t%.2f\t%d\t%d\t%s\n",
		movie->title, movie->year,	movie->run_time, 
		movie->average_rating, movie->num_votes, movie->distribution,
		movie->genre
	);
	//printf("\n");
}