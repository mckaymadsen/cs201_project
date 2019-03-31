#ifndef _movie_H_
#define _movie_h_

typedef struct Movie
{	
	char id[11];			//imdb given uniqie ID
	char title[100];		//Title of movie
	unsigned long location;	//array location/hash key
	int year;				//Year movie was released
	char run_time[15];		//runtime for the movie
	char genre[100];		//top genres
	double average_rating;	//average rating
	int num_votes;			//number of votes for rating
	int distribution;		//1 = Blue Ray, 2 = DVD, 3 = Digital
} Movie;

extern Movie **newArray(unsigned int size);
extern Movie *initalize(void);
extern Movie *newMovie(FILE *fptr, int cat_flag, char buff[1024]);
extern void print_movie(Movie *movie);

#endif