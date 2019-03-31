/*  
 *  Filename:       main.c
 *  Author:         McKay Madsen
 *  Date:           3/27/19
 *  Version:        2.2
 *  Description:
 *    
 *  Notes:
 * 		Requires: UI.c, catalog.c, hash.c, movie.c and corresponding header files
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "movie.h"
#include "UI.h"
#include "catalog.h"
#include "hash.h"


void add_movie(Hash_table *hash_array, Catalog *current_catalog, int max_search);


int main() 
{
	int max_catalog = 50;
	int num_elements = 511709;
	int max_search = 15;

	int load_flag = 0;

	Hash_table *hash_array = newHash_table(num_elements);
	Catalog *current_catalog = newCatalog(max_catalog);

	display_start();
	
	printf("\n\tLoading dataset ");
	load_flag = load_database(hash_array);
	if (load_flag == -1)	return 0;			//failsafe for bad data file

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
					else printf("\tRemoval fail. Make sure you enetered an existing/allowed filename.\n");
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
								add_movie(hash_array, current_catalog, max_search);
								break;
							case 3: // delete movie
								delete_movie(current_catalog);
								break;
							case 4:	//save catalog to file
								save_catalog(current_catalog);
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
					else if(read_catalog_choice == 4) save_catalog(current_catalog);					

					read_catalog_choice = 0;		//reset choice
					break;

				case 1 :	//CREATE 
					create_catalog_display(max_catalog);
					create_catalog_choice = create_catalog_input();

					if (create_catalog_choice == 3) break;
					else if (create_catalog_choice == 1)
					{
						int result = create_catalog();
						if(result != -1)
							printf("\n\tCatalog created sucessfully!\n");//goto main menu somehow
					}
					else if (create_catalog_choice == 2)
					{
						int result = clear_current_catalog(current_catalog);
						if(result != -1)
							printf("\n\tCleared current catalog!\n");
					}
					create_catalog_choice = 0;	//reset choice
					break;

				case 0 :
					printf("Yikes, nothing happened in main_menu_input");
					break;
				default : 
					printf("somthing went wrong");
					break;
			}
	}	
	free(hash_array);	
	free(current_catalog);

	return 0;
}


/*******************FUNCTIONS**********************/

/*
 * This function adds movies to the current catalog. To add a movie, the user is prompted
 * to enter a search term to look for a movie. There are 2 search options: 1. Exact title
 * search and 2. Substring search. For substring, a list of results is returned and they 
 * can then chose a title from the (limited) results to add to the current catalog.
 */
void add_movie(Hash_table *hash_array, Catalog *current_catalog, int max_search)
{
	int found = 0, selector = 0;
	long search_exact_result = -1;
	long selected_result = 0;
	
	unsigned long search_results[max_search];		
	for(int j = 0; j < max_search; j++)			//set all to 0
	{
		search_results[j] = 0;
	}

	printf("\n\tThere are 2 types of searching available. Enter \"1\" for an exact title search.");
	printf("\n\tThis will give the faster search time, but requires an exact title (i.e. \"Star Wars\".");
	printf("\n\tThere may be duplicate titles present. This search will return the first one found. If it is");
	printf("\n\tnot theone you are looking for, use the substring search option to pull all occurences.");
	printf("\n\n\tEnter \"2\" for a substring search. This is slower, but returns any title with an occurance");
	printf("\n\tof the search term.\n\n\tEnter choice: ");

	//fgets(search_term, 1024, stdin);
	selector = search_hash_choice();			//get choice for exact search or substring
	if (selector == -1) return;	
	
	if (selector == 2)//substring search selected
	{	
		search_hash_display(max_search);
		
		char search_term[1024];

		fgets(search_term, 1024, stdin);
		char *p = strrchr(search_term, '\n');  	//removes trailing newline from search term
		if (p != NULL) *p = '\0';				//replaces with terminating char

		printf("\n");
		if(search_term == NULL || strlen(search_term) < 3 || strlen(search_term) > 150) 
		{
			printf("\tInvalid input. Please restart the search process\n");
			return;
		}
		
		if (search_hash(search_term, search_results, hash_array, max_search) != -1)	//if search_hash finds something
		{   
			printf("\n\t     Title (first 30 characters)     Year    Run Time    Rating   Votes      Genre \n");
			int i;
			for (i = 0; i<max_search; i++)
			{			
				if (search_results[i] != 0)
				{
					printf("\t%2d. ",i+1);
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

		selected_result = search_results[selected_movie-1];
	}
	else if (selector == 1)						//exact search selected
	{
		search_hash_display(max_search);	
			
		char search_term[1024];
		fgets(search_term, 1024, stdin);
		char *p = strrchr(search_term, '\n');  	//removes trailing newline from search term
		if (p != NULL) *p = '\0';				//replaces with a terminating char

		printf("\n");
		if(search_term == NULL || strlen(search_term) < 3 || strlen(search_term) > 150) 
		{
			printf("\tInvalid input. Please restart the search process\n");
			return;
		}
		
		search_exact_result = search_exact_hash(search_term,hash_array);
		if (search_exact_result == -1)
		{
			printf("\n\tNo results found. Please try again or use the substing search");
			return;
		}

		printf("\n\tMovie found!\n\t");
		print_hash_location(search_exact_result, hash_array);
		selected_result = search_exact_result;
	}

	int distribution = dis_input(); 		//get distribution method
	if (distribution == -1) return;

	//select result and add to current catalog
	for(int j = 0; j < current_catalog->capacity; j++)
	{
		if (current_catalog->movie[j]->distribution == 0)
		{	
			current_catalog->movie[j] = hash_array->movie[selected_result];
			current_catalog->movie[j]->distribution = distribution;
			current_catalog->size++;
			printf("\n\tItem added!");
			break;
		}
		else if (j >= current_catalog->capacity-1)
		{
			printf("\n\tCatalog Full, please delete a move or create a new catalog\n");
		}		
	}

	found = 0;
	return;
}







