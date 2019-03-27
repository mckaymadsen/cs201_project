/*  Filename:       main.c
 *  Author:         McKay Madsen
 *  Date:           3/15/19
 *  Version:        2.0
 *  Description:
 *    TODO
 *  Notes:
 * 		Requires: UI.c
 *  TODO:
 * 		removle movies from catalog, clean up, fix search
 * optimize
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "UI.h"

#define num_elements 36	//numer of elements in dataset
#define max_search 15
#define max_catalog_def 50 //catalog
//#define num_elements 511709 //(movies)

struct movie 
{	
	char id[11];			//imdb given uniqie ID
	char title[150];		//Title of movie
	unsigned long location;	//array location/hash key
	int year;				//Year movie was released
	char run_time[15];
	char genre[100];		//top genres
	double average_rating;	//average rating
	int num_votes;			//number of votes for rating
	int distribution;		//1 = Blue Ray, 2 = DVD, 3 = Digital
};

//structures
struct movie *dummy_item;
struct movie *hash_array[num_elements];
struct movie *current_catalog[max_catalog_def];

struct movie *delete(struct movie *item);

void load_database(void);
unsigned long hash_function(char *title);

long search_hash(char search_term[50], long search_results[max_search]);

//manage catalog functions
void load_catalog(char filename[55]);
void display_catalog(void);
void save_catalog(int number_of_entries);
int create_catalog(void);
int remove_catalog(void);
int open_catalog(int load_flag);

//update catalog functions
void add_movie(void);
void delete_movie();

//driver functions
int size_current_catalog(void);
void print_hash_location(int location);

int main() 
{
	int max_catalog = max_catalog_def;
	display_start();
	
	printf("\n\tLoading dataset ");
	load_database();
	printf("Load Complete\n");	

	int main_menu_choice = 0;
	int update_catalog_choice = 0;
	int create_catalog_choice = 0;
	int read_catalog_choice = 0;

	int remove_catalog_result = 0;
	//int ucc_exit = 0;
	//int exit_flag = 0;

	while(main_menu_choice != -1)	//looop until exit xuit
	{
		//flags for loops
		int ucc_exit = 0;

		main_menu_display();
		main_menu_choice = main_menu_input();
		if (main_menu_choice == -1) break;
		
		//printf("\nuser choice: %d\n", main_menu_choice); //debug

			switch(main_menu_choice)
			{
				case 4 :	//REMOVE
					remove_catalog_result = remove_catalog();
					if (remove_catalog_result == 0) printf("\n\tCatalog removed\n");
					else printf("\tRemoval fail. Make sure you enetered an existing filename.\n");
					break;
				case 3 :	//UPDATE -- TODO
					while(!ucc_exit)
					{	
						update_catalog_display(max_catalog);
						update_catalog_choice = update_catalog_input();
						if (update_catalog_choice == -1) break;

						switch(update_catalog_choice)
						{
							case 1:	//Display current
								display_catalog();
								break;
							case 2:	//add movie
								add_movie();
								break;
							case 3: // delete movie
								delete_movie();
								break;
							case 4:	//save catalog to file
								save_catalog(size_current_catalog());
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
				case 2 :	//LOAD -- TODO
					read_catalog_display(max_catalog);
					read_catalog_choice = read_catalog_input();

					if (read_catalog_choice == 5) break;
					else if(read_catalog_choice == 1) open_catalog(0);
					else if(read_catalog_choice == 2) display_catalog();
					else if(read_catalog_choice == 3) open_catalog(1);
					else if(read_catalog_choice == 4) save_catalog(size_current_catalog());					

					read_catalog_choice = 0;		//reset choice
					break;

				case 1 :	//CREATE -- TODO
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
	return 0;
}


/*******************FUNCTIONS**********************/

/*
 * This function loads the database. It reads in a line from the defeined datafile
 * and parses it into a temorary item using strtok. The title is the hashed to get
 * the hash location. The DJBZ hash algrothim is used. Linear probing is used to resolve 
 * collisions. The hash table is hard coded to have enough slots to fit all results. 
 */
void load_database(void)
{
	FILE *fptr;								//create the file opener
	//fptr = fopen("cs201database_TAB.txt", "r");		//open database 
	fptr = fopen("test_data2.txt", "r");
	//char trash[25];
	char buff[BUFSIZ];
	int q = 1;
	int i = 0;

	while (i < num_elements)				//Read until number of items is complete (bad way, but it works)
	{
		struct movie *item = (struct movie*) malloc(sizeof(struct movie));	//create new item with malloc
		if (item == NULL)
		{
			printf("error allocating memory for movie %d\n", i);
		}

		fgets(buff, BUFSIZ, fptr);
		char *token = strtok(buff,"\t");
		strcpy(item->id, token);
		token = strtok(NULL,"\t");
		strcpy(item->title, token);
		token = strtok(NULL,"\t");	//trash
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
		item->distribution = 0;


		long hash_index = hash_function(item->title) % num_elements;		//get hash_index
		
		//add item to hash table
		while(hash_array[hash_index] != NULL && hash_array[hash_index]->location != -1)
		{
			//go to next cell
			//++hash_index;	
			//hash_index = hash_index %= num_elements;			
			//wrap around the table
			hash_index = (hash_index + (q * q))% num_elements;
		}
		hash_array[hash_index] = item;
		hash_array[hash_index]->location = hash_index;

		/*printf("\n%s,  %s, %d, %s, %f, %d, %s\n",
			item->id, 	item->title, item->year, item->run_time, item->average_rating, item->num_votes, item->genre
		);
		printf("\n");*/

		//if(i%2 == 0) printf(". ");
		if(i%75000 == 0) printf(". ");
		i++;
	}

	fclose(fptr);
	return;
}

/*
 * The function frees the struct
 */
struct movie *delete(struct movie *item)
{
	//long hash_index = item->key;
	free(item);	
	return NULL;
}

/*
 * This function returns the hash value when given a string
 * It is a copy of the DJB2 hash function see here:
 * http://www.cse.yorku.ca/~oz/hash.html
 */ 
unsigned long hash_function(char *title)
{
	/*long key = 0;
	//hashign fucntion here
	key = title[100] % num_elements;
	return key;*/
	
  unsigned long hash = 5381;
  int c;
  while ((c = *title++) != 0)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;

}

/*
 * This function searches for string matches in the hash table.
 * The string to be searched for is put into the hash function
 * and the returned index is used as a starting point. This is not
 * a very effiecent searach for partial strings, but will give 
 * close to O(1) results when the exact title is used. 
 */
long search_hash(char search_term[50],long search_results[max_search])
{
	int start_index = hash_function(search_term) % num_elements;
	int index = start_index;
	int searched = 0;
	int found = 0;

	while (hash_array[index] != NULL && found < max_search && searched < num_elements)
	{
		char *pch = strstr(hash_array[index]->title, search_term);
		if ( pch != NULL) //if matching substirng is found
		{			
			search_results[found] = hash_array[index]->location;
			found++;
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
	printf("\tEnter the name of the catalog you'd like to create. Try to stay below 50 \n");
	printf("\talphanumeric characters for ease of use. Name: ");

	char buf[BUFSIZ];
	fgets(buf, BUFSIZ, stdin);
  sscanf(buf, "%s", name);
	//ADD in error checking for size

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
int open_catalog(int load_flag)
{
	//get catalog name and display catalog
	char name[55] = "\0";// = "";
	int not_valid_file = 0;
	while(not_valid_file == 0)
	{
		printf("\n\tEnter the name of the catalog you'd like to read. \n");
		printf("\n\tType \"Return\" to stop. \n");
		printf("\tInclude the file extension: ");

		char buf[BUFSIZ];
		fgets(buf, BUFSIZ, stdin);
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
		load_catalog(name);
		if (!load_flag)	display_catalog();			
		return 1;
	}	
	return 0;
}

/*
 * This function loads a text file containing movie data into the current catalog.
 * 
 * TODO: add in new way to read file
 */
void load_catalog(char filename[55])
{
	FILE *fptr;
	fptr = fopen(filename, "r"); 
	if (fptr == NULL)
	{
			printf("\nFileread Error. Please try again with the correct title.");
	}

	char trash[25];
	int num_movies = 0;
	fscanf(fptr," %d", &num_movies);

	for (int i = 0; i < num_movies; i++)
	{
		struct movie *item = (struct movie*) malloc(sizeof(struct movie));	//create new item with malloc
		if (item == NULL)
		{
			printf("error allocating memory for movie %d\n", i);
		}

		fscanf(fptr,
		 	"%10[^\t]\t	%100[^\t]\t %20[^\t]\t	 	  %d\t	  	   %10[^\t]\t		   %lf\t					  %d\t 				%25s %d",
			item->id, item->title,	trash, &item->year, item->run_time, &item->average_rating, &item->num_votes, item->genre, &item->distribution
		);

		current_catalog[i] = item;
	}

	printf("\n\tCatalog Loaded Sucessfully\n");
}

/*
 * This fucntion displays the values in the current catalog.
 */
void display_catalog()
{
	printf("\n\tCatalog: \n\tTitle (first 30 characters)   \t\tYear\tRun Time\tRating\tVotes\tDistribution\n");
	for (int i = 0; i < max_catalog_def; i++)
	{
		//if (current_catalog[i] == NULL && i == 0) printf("\n\tCatalog Empty, add movies through the main screen\n");
		if (size_current_catalog() == 0)
		{
			printf("\n\tCatalog Empty, add movies through the main screen\n");
			return;
		}
		else if (current_catalog[i] != NULL)
		{	
			printf("\n\t%d.", i+1);	
			printf(" %-30.30s\t%d\t%s\t\t%.2f\t%d\t%s",
				current_catalog[i]->title, 
				current_catalog[i]->year,	current_catalog[i]->run_time, current_catalog[i]->average_rating, 
				current_catalog[i]->num_votes, current_catalog[i]->genre
			);
			if (current_catalog[i]->distribution == 1) printf("\t%s"," Distro: BluRay");
			if (current_catalog[i]->distribution == 2) printf("\t%s"," Distro: DVD");
			if (current_catalog[i]->distribution == 3) printf("\t%s"," Distro: Digital");
		}
	}
	printf("\n");
}

/*
 * This function adds movies to the current catalog. To add a movie, the user is prompted
 * to enter a search term to look for a movie. THe can then chose a title from the (limited)
 * results to add to the current directory.
 */
void add_movie()
{
	//char search_term[155];
	int found = 0;
	
	search_hash_display(max_search);
	
	//char buf[BUFSIZ];
	char search_term[BUFSIZ];
  //fgets(buf, BUFSIZ, stdin);
  //sscanf(buf, "%s", search_term);

	fgets(search_term, BUFSIZ, stdin);
	search_term[strlen(search_term)-1] = '\0'; //remove newline char for search comparison

	printf("\n");
	if(search_term == NULL || strlen(search_term) < 3 || strlen(search_term) > 150) 
	{
		printf("\tInvalid input. Please restart the search process\n");
		return;
	}

	long search_results[max_search] = {0};
	if (search_hash(search_term, search_results) != -1)
	{   
		printf("\tMovie result format:\n\tMovie title, Year, Runtime, Average Rating, Number of Votes, Genre\n\n"); 
		int i;
		for (i = 0; i<max_search; i++)
		{			
			if (search_results[i] != 0)
			{
				printf("\t%d. ",i+1);
				print_hash_location(search_results[i]);
				found++;
			}
		}
	}
	else
	{
		printf("\n\tNo Matches\n");
		return;
	}

	printf("\t%d Results Found!\n",found);
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
		if (current_catalog[j] == NULL)
		{
			current_catalog[j] = hash_array[search_results[selected_movie-1]];
			current_catalog[j]->distribution = distribution;
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
 * TODO
 */
void delete_movie()
{

}

/*
 * This function writes the current catalog to a given filename.
 */
void save_catalog(int number_of_entries)
{
	char filename[55];
	char buf[BUFSIZ];
	char *trash = "bogus";

	printf("\n\tEnter the filename you want to save the current catalog to. If you\n ");
	printf("\tenter an existing filename, it will be overwritten. Make sure you have loaded\n");
	printf("\tthe catalog before adding movies to it.\n\n\tEnter filename: ");
	fgets(buf, BUFSIZ, stdin);
	sscanf(buf, "%s", filename);

	FILE *fptr;
	fptr = fopen(filename, "w"); 
	if (fptr == NULL)
	{
			printf("\nFileread Error. Please try again.");
	}

	fprintf(fptr, "%d", size_current_catalog());
	for (int i = 0; i < max_catalog_def; i++)
	{
		if (current_catalog[i] != NULL)
		{
			fprintf(fptr,	"%s\t%s\t%s\t%d\t%s\t%lf\t%d\t%s\t%d",
			current_catalog[i]->id, current_catalog[i]->title,	trash, current_catalog[i]->year, 
			current_catalog[i]->run_time, current_catalog[i]->average_rating, current_catalog[i]->num_votes, current_catalog[i]->genre, 
			current_catalog[i]->distribution
			);
		}
	}
	fclose(fptr);
	return;
}

int remove_catalog()
{
	char buf[BUFSIZ];
	char filename[155];
	printf("\n\tWelcome to remove a catalog menu. Enter the filename of the catalog\n");
	printf("\tyou'd like to remove: ");

	fgets(buf, BUFSIZ, stdin);
	sscanf(buf, "%s", filename);

	int status = remove(filename);
	return status;
}
/*
 * Returns the number of non NULL slots in the current catalog
 */

int size_current_catalog()
{
	int size = 0;
	for(int j = 0; j < max_catalog_def; j++)
	{
		if (current_catalog[j] != NULL)
		{
			size++;
		}
	}
	return size;
}

/*
 * This function prints out the data at a given hash location in the table.
 */
void print_hash_location(int location) 
{
		printf("%s\t%d\t%s\t%.2f\t%d\t%s \n",
		hash_array[location]->title, hash_array[location]->year,	hash_array[location]->run_time, 
		hash_array[location]->average_rating, hash_array[location]->num_votes, 
		hash_array[location]->genre
	);
	printf("\n");
}