/*  
 *  Filename:       main.c
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

//#define num_elements 36	//numer of elements in dataset
//#define num_elements 511687	//numer of elements in dataset
#define max_search 15
#define max_catalog_def 50 //catalog
#define num_elements 511709 //(movies)


//ISSUE IS MEMORYSIZE. Stops working when the fill; files is used
//look at using malloc instead of regular 

typedef struct  
{	
	char id[11];			//imdb given uniqie ID
	char title[100];		//Title of movie
	unsigned long location;	//array location/hash key
	int year;				//Year movie was released
	char run_time[15];
	char genre[100];		//top genres
	double average_rating;	//average rating
	int num_votes;			//number of votes for rating
	int distribution;		//1 = Blue Ray, 2 = DVD, 3 = Digital
}Movie;

typedef struct 
{
	Movie *movie;
}Hash_table;


typedef struct 
{
	Movie *movie;
}Catalog;

/*//structures
struct movie *dummy_item;
struct movie *current_catalog[max_catalog_def];
//struct movie *hash_array[num_elements];
//struct movie *current_catalog[max_catalog_def];*/

//struct functions
Movie *initalize(void);


//manage catalog functions
void load_catalog(char *filename, Catalog *current_catalog);
void display_catalog(Catalog *current_catalog);
void save_catalog(int number_of_entries, Catalog *current_catalog);
int create_catalog(void);
int remove_catalog(void);
int open_catalog(int load_flag, Catalog *current_catalog);

//update catalog functions
void add_movie(Hash_table *hash_array, Catalog *current_catalog);
void delete_movie(Catalog *current_catalog);

//driver functions
int size_current_catalog(Catalog *current_catalog);

void print_movie(Movie *movie);
void print_hash_location(unsigned long loc, Hash_table *hash_array);

void load_database(Hash_table *hash_array);
unsigned long hash_function(char *title);
long search_hash(char search_term[50], unsigned long search_results[max_search], Hash_table *hash_array);


int main() 
{
	int max_catalog = max_catalog_def;

	Hash_table *hash_array = (Hash_table*)malloc(num_elements * sizeof(Movie*));
	for (int x = 0; x < num_elements; x++)
	{
		hash_array[x].movie = malloc(sizeof(Movie));
		hash_array[x].movie = initalize();
	}

	Catalog *current_catalog = (Catalog*)malloc(max_catalog_def * sizeof(Movie*));
	for (int y = 0; y < max_catalog_def; y++)
	{
		current_catalog[y].movie = malloc(sizeof(Movie));
		current_catalog[y].movie = initalize();
	}	

	display_start();
	
	printf("\n\tLoading dataset ");
	load_database(hash_array);
	printf("Load Complete\n");	

	int main_menu_choice = 0;
	int update_catalog_choice = 0;
	int create_catalog_choice = 0;
	int read_catalog_choice = 0;

	int remove_catalog_result = 0;

	/*
	 * This is the main driver for the UI setup
	 */
	while(main_menu_choice != -1)	//loop until exit xuit
	{
		//flags for loops
		int ucc_exit = 0;

		main_menu_display();
		main_menu_choice = main_menu_input();
		if (main_menu_choice == -1) break;
		
			switch(main_menu_choice)
			{
				case 4 :	//REMOVE
					remove_catalog_result = remove_catalog();
					if (remove_catalog_result == 0) printf("\n\tCatalog removed\n");
					else printf("\tRemoval fail. Make sure you enetered an existing filename.\n");
					break;
				case 3 :	//UPDATE 
					while(!ucc_exit)
					{	
						update_catalog_display(max_catalog);
						update_catalog_choice = update_catalog_input();
						if (update_catalog_choice == -1) break;

						switch(update_catalog_choice)
						{
							case 1:	//Display current
								display_catalog(current_catalog);
								break;
							case 2:	//add movie
								add_movie(hash_array, current_catalog);
								break;
							case 3: // delete movie
								delete_movie(current_catalog);
								break;
							case 4:	//save catalog to file
								save_catalog(size_current_catalog(current_catalog), current_catalog);
								break;	
							case 5: //exit
								ucc_exit = 1;
								break;
							default:
								break;
						}
					}	
					update_catalog_choice = 0;		//reset choice
					break;
				case 2 :	//LOAD 
					read_catalog_display(max_catalog);
					read_catalog_choice = read_catalog_input();

					if (read_catalog_choice == 5) break;
					else if(read_catalog_choice == 1) open_catalog(0, current_catalog);
					else if(read_catalog_choice == 2) display_catalog(current_catalog);
					else if(read_catalog_choice == 3) open_catalog(1, current_catalog);
					else if(read_catalog_choice == 4) save_catalog(size_current_catalog(current_catalog), current_catalog);					

					read_catalog_choice = 0;		//reset choice
					break;

				case 1 :	//CREATE 
					create_catalog_display(max_catalog);
					create_catalog_choice = create_catalog_input();

					if (create_catalog_choice == 2) break;
					else if (create_catalog() == 1) printf("\n\tCatalog created sucessfully!\n");//goto main menu somehow
					
					create_catalog_choice = 0;	//reset choice
					break;

				case 0 :
					printf("Yikes, nohting happened in main_menu_input");
					break;
				default : 
					printf("somthing went wrong");
					break;
			}
	}	
	free(hash_array);	
	free(current_catalog);
	//free(movie);
	return 0;
}


/*******************FUNCTIONS**********************/

/*
 * This function loads the database. It reads in a line from the defeined datafile
 * and parses it into a temorary item using strtok. The title is the hashed to get
 * the hash location. The DJBZ hash algrothim is used. Linear probing is used to resolve 
 * collisions. The hash table is hard coded to have enough slots to fit all results. 
 */
void load_database(Hash_table *hash_array)
{
	FILE *fptr;										//create the file opener
	//fptr = fopen("cs201database_TAB.txt", "r");		//open database 
	//fptr = fopen("test_data2.txt", "r");//debug
	fptr = fopen("finalV3.txt", "r");
	
	char buff[1024];
	int q = 1;
	int i = 0;

	while (i < num_elements)						//Read until number of items is complete (bad way, but it works)
	{
		Movie *item = malloc(sizeof(Movie));	//create new item with malloc
		if (item == NULL)
		{
			printf("error allocating memory for movie %d\n", i);
		}
		
		fgets(buff, 1024, fptr);
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
		token = strtok(NULL,"\t");
		strcpy(item->genre, token);
		token = strtok(NULL,"\t");

		char *p = strrchr(item->genre, '\n');  		//removes trailing newline from genre in mainfile
		if (p != NULL) *p = '\0';
		
		item->distribution = 0;


		long hash_index = hash_function(item->title) % num_elements;		
		
		//add item to hash table
		while(strcmp(hash_array[hash_index].movie->title, "\0") != 0)
		{			
			//wrap around the table with quadradic probing
			hash_index = (hash_index + (q * q))% num_elements;
		}
		hash_array[hash_index].movie = item;
		//hash_array->movie[hash_index] = *item;
		hash_array[hash_index].movie->location = hash_index;
		//print_movie(hash_array[hash_index].movie); //debug

		if(i%75000 == 0) printf(". ");
		i++;
		//free(item);
	}
	
	fclose(fptr);
	return;
}

/*
 * This function returns the hash value when given a string
 * It is a copy of the DJB2 hash function see here:
 * http://www.cse.yorku.ca/~oz/hash.html
 */ 
unsigned long hash_function(char *title)
{
  unsigned long hash = 5381;
  int c;
  while ((c = *title++) != 0)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
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
	if (num_movies == 0) 
	{
		printf("\n\tCatalog blank or corrupted, please load a different one.\n");
	} 
	for (int i = 0; i < num_movies; i++)
	{
		Movie *item = (Movie *)malloc(sizeof(Movie));	//create new item with malloc
		if (item == NULL)
		{
			printf("error allocating memory for movie %d\n", i);
		}

		//pull the file line by line and tokenize based on the '\t' character
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
		token = strtok(NULL,"\n");
		strcpy(item->genre, token);
		
		char *p = strrchr(item->genre, '\n');  	//removes trailing newline from mainfile
		if (p != NULL) *p = '\0';
		
		/*token = strtok(NULL,"\t");
		item->distribution = atoi(token);*/

		current_catalog[i].movie = item;
		//fgets(buff, 1024, fptr);
	}
	for (int j = num_movies; j < max_catalog_def; j++)
	{
		current_catalog[j].movie = initalize();
	}
	
	printf("\n\tCatalog Loaded Sucessfully\n");
}

/*
 * This fucntion displays the values in the current catalog.
 */
void display_catalog(Catalog *current_catalog)
{
	printf("\n\tCatalog: \n\tTitle (first 30 characters)   \t\tYear\tRun Time\tRating\tVotes\tDistribution\tGenre\n");
	for (int i = 0; i < max_catalog_def; i++)
	{
		if (size_current_catalog(current_catalog) == 0)
		{
			printf("\n\tCatalog Empty, add movies through the main screen\n");
			return;
		}

		else if (current_catalog[i].movie->distribution > 0)
		{	
			printf("\n\t%d.", i+1);	
			printf(" %-30.30s\t%d\t%s\t\t%.2f\t%d",
				current_catalog[i].movie->title, 
				current_catalog[i].movie->year,	current_catalog[i].movie->run_time, current_catalog[i].movie->average_rating, 
				current_catalog[i].movie->num_votes 
			);
			if (current_catalog[i].movie->distribution == 1) printf("\t%s"," BluRay");
			if (current_catalog[i].movie->distribution == 2) printf("\t%s"," DVD");
			if (current_catalog[i].movie->distribution == 3) printf("\t%s"," Digital");

			printf("\t%s",current_catalog[i].movie->genre);
		}
	}
	printf("\n");
}

/*
 * This function adds movies to the current catalog. To add a movie, the user is prompted
 * to enter a search term to look for a movie. THe can then chose a title from the (limited)
 * results to add to the current directory.
 */
void add_movie(Hash_table *hash_array, Catalog *current_catalog)
{
	int found = 0;
	search_hash_display(max_search);
	
	char search_term[1024];

	fgets(search_term, 1024, stdin);
	char *p = strrchr(search_term, '\n');  	//removes trailing newline from mainfile
	if (p != NULL) *p = '\0';

	printf("\n");
	if(search_term == NULL || strlen(search_term) < 3 || strlen(search_term) > 150) 
	{
		printf("\tInvalid input. Please restart the search process\n");
		return;
	}


	unsigned long search_results[max_search] = {0};
	if (search_hash(search_term, search_results, hash_array) != -1)
	{   
		printf("\tMovie result format:\n\tMovie title, Year, Runtime, Average Rating, Number of Votes, Genre\n\n"); 
		int i;
		for (i = 0; i<max_search; i++)
		{			
			if (search_results[i] != 0)
			{
				printf("\t%d. ",i+1);
				print_hash_location(search_results[i], hash_array);
				found++;
			}
		}
	}
	else
	{
		printf("\n\tNo Matches\n");
		return;
	}

	//show results and add a movie
	printf("\n\t%d Results Found!\n",found);
	if (found == 0)
	{
		printf("\tPlease try to add a movie again.\n");
		return;
	}
	int selected_movie = select_movie_input(found);
	if (selected_movie == -1) return;

	int distribution = dis_input(); 
	if (distribution == -1) return;

	//select result and add to current catalog
	for(int j = 0; j < max_catalog_def; j++)
	{
		if (current_catalog[j].movie->distribution == 0)
		{	
			current_catalog[j].movie = hash_array[search_results[selected_movie-1]].movie;
			current_catalog[j].movie->distribution = distribution;
			printf("\n\tItem added!");
			break;
		}
		else if (j == max_catalog_def-1)
		{
			printf("\n\tCatalog Full, please delete a move or create a new catalog\n");
		}		
	}

	found = 0;
	return;
}

/*
 * This function searches for string matches in the hash table.
 * The string to be searched for is put into the hash function
 * and the returned index is used as a starting point. This is not
 * a very effiecent searach for partial strings, but will give 
 * close to O(1) results when the exact title is used. 
 */
long search_hash(char *search_term, unsigned long search_results[max_search], Hash_table *hash_array)
{
	int start_index = hash_function(search_term) % num_elements;
	int index = start_index;
	int searched = 0;
	int found = 0;

	while (strcmp(hash_array[index].movie->title, "\0") != 0 && found < max_search && searched < num_elements) 
	{
		char *pch = strstr(hash_array[index].movie->title, search_term);
		if ( pch != NULL) 		//if matching substirng is found
		{			
			search_results[found] = hash_array[index].movie->location;
			found++;
		}	

		index++;
		index %= num_elements;

		searched++;
	}
	if (searched == 0)	return -1;
	printf("%d", found);
	printf("\t%d", searched);
	return 0;
}

/* 
 * This function goes tot he given location and shifts the items in the array down by 1 to delete
 * the selected movie.
 */
void delete_movie(Catalog *current_catalog)
{
	int cat_size = size_current_catalog(current_catalog);
	display_catalog(current_catalog);
	int movie_choice = remove_cat_display(cat_size);
	
	if (movie_choice == -1)
	{
		printf("\n\tMovie removal unsucessful, please try again\n");
		return;
	}

	for (int i = movie_choice-1; i < max_catalog_def; i++)
	{
		if (i < max_catalog_def-1)
			current_catalog[i] = current_catalog[i+1]; 
	}

	printf("\n\tMovie Sucessfully Removed\n");
	return;
}

/*
 * This function writes the current catalog to a given filename.
 */
void save_catalog(int number_of_entries, Catalog *current_catalog)
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

	fprintf(fptr, "%d", size_current_catalog(current_catalog));
	for (int i = 0; i < max_catalog_def; i++)
	{
		if (current_catalog[i].movie->distribution > 0)
		{
			/*char *p = strrchr(current_catalog[i].movie->genre, '\n');  	//removes trailing newline from mainfile
			if (p != NULL) *p = '\0';*/

			fprintf(fptr,	"\n%s\t%s\t%s\t%d\t%s\t%lf\t%d\t%d\t%s",
			current_catalog[i].movie->id, current_catalog[i].movie->title,	trash, current_catalog[i].movie->year, 
			current_catalog[i].movie->run_time, current_catalog[i].movie->average_rating, current_catalog[i].movie->num_votes, 
			current_catalog[i].movie->distribution,	current_catalog[i].movie->genre 
			
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

/*
 * Returns the number of non NULL slots in the current catalog
 */
int size_current_catalog(Catalog *current_catalog)
{
	int size = 0;
	for(int j = 0; j < max_catalog_def; j++)
	{
		if (current_catalog[j].movie->distribution > 0)
		{
			size++;
		}
	}
	return size;
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

void print_hash_location(unsigned long loc, Hash_table *hash_array)
{
		printf("\t%-30.30s\t%d\t%s\t\t%.2f\t%d\t%s\n",
		hash_array[loc].movie->title, hash_array[loc].movie->year,	hash_array[loc].movie->run_time, 
		hash_array[loc].movie->average_rating, hash_array[loc].movie->num_votes, 
		hash_array[loc].movie->genre
	);
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