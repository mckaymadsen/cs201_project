/*  Filename:       hash.c
 *  Author:         McKay Madsen
 *  Updated:        3/30/19
 *  Description:
 *      Contains the hash table data structure and corresponding functions
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "movie.h"
#include "hash.h"


/*
 *	Constructor for hashtable. Mallocs the table and all components.
 *	The initalize function mallocs and sets the location values to NULL or 0	
 */
Hash_table *newHash_table(unsigned int num_elements)
{
    Hash_table *hash_array = (Hash_table*)malloc(sizeof(Hash_table));

    hash_array->empty = malloc(sizeof(int)*num_elements);
    hash_array->movie = newArray(num_elements);
    for(int i = 0; i < num_elements; i++)
    {
            hash_array->movie[i] = initalize();
            hash_array->empty[i] = 1;
    }

    hash_array->size = num_elements;
    return hash_array;
}


/*
 * This function loads the database. It reads in a line from the defeined datafile
 * and parses it into a temorary item using strtok. The title is the hashed to get
 * the hash location. The DJBZ hash algrothim is used. Linear probing is used to resolve 
 * collisions. The hash table is hard coded to have enough slots to fit all results. 
 */
int load_database(Hash_table *hash_array)
{
	FILE *fptr;										//create the file opener
	fptr = fopen("cs201combined_TAB.txt", "r");		//open database 
	if (fptr == NULL)
	{
		printf("Error loading database. Check the filename/readme. Exiting\n");
		return -1;
	}
		
	char buff[1024];
	//int q = 1;
	int i = 0;
    
	//while (i < hash_array->size)						//Read until number of items is complete (bad way, but it works)
	while(fgets(buff,1024,fptr))
	{
		Movie *item = newMovie(fptr, 0, buff);
		unsigned long hash_index = 0; 		
		
		//add item to hash table
		/*while(hash_array->empty[i] != 0)
		{			
			//wrap around the table with quadradic probing
			hash_index = (hash_index + (q * q))% hash_array->size;
		}*/

        for(unsigned int q = 0; q < hash_array->size; q++)
        {
            hash_index = (hash_function(item->title) + (q * q)) % hash_array->size;
            if(hash_array->empty[hash_index]) break;
        }

		hash_array->movie[hash_index] = item;
		hash_array->movie[hash_index]->location = hash_index;
        hash_array->empty[hash_index] = 0;

		if(i%75000 == 0) printf(". ");
		i++;
	}
	
	fclose(fptr);
	return 1;
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
 * This function searches for string matches in the hash table.
 * The string to be searched for is put into the hash function
 * and the returned index is used as a starting point. This is not
 * a very effiecent searach for partial strings, but will give 
 * close to O(1) results when the exact title is used. 
 */
long search_hash(char *search_term, unsigned long search_results[], Hash_table *hash_array, int max_search)
{
	//ADD EXACT SEARCH
    //int num_ele = hash_array->size;
    int search_array[511709] = {0};//		//SET TO NUM ELEMENTS IN CATALOG
	unsigned long index;// = start_index;
	unsigned int searched = 0;
	int found = 0, j = 0;

	while ((found < max_search) && (searched < hash_array->size)) 
	{
		index = (hash_function(search_term) + (j * j)) % hash_array->size;
		if (!search_array[index])
		{		
			char *pch = strstr(hash_array->movie[index]->title, search_term);
			if ( pch != NULL) 		//if matching substirng is found
			{			
				search_results[found] = hash_array->movie[index]->location;
				
				found++;
			}	
			search_array[index] = 1;
			searched++;
		}
		j++;
	}
	
	if (searched == 0)	return -1;

	return 0;
}


/*
 *	This function searchs for an exact match and returns it with a ~O(1) search time.
 * 	Only works with exact titles.
 */
long search_exact_hash(char *search_term, Hash_table *hash_array)
{
	unsigned long hash_index = hash_function(search_term) % hash_array->size;
    for(unsigned int q = 0; q < hash_array->size; q++)
    {
        hash_index = (hash_function(search_term) + (q * q)) % hash_array->size;
        if(strcmp(search_term, hash_array->movie[hash_index]->title) == 0) 
		{
			return hash_index;
		}
    }
	return -1;
}


/*
 *	Prints out the formatted data of a given location in the hash table
 */
void print_hash_location(unsigned long loc, Hash_table *hash_array)
{
	printf(" %-30.30s  %-6d  %-8s    %-7.2f  %-11d%-13s\n",
		hash_array->movie[loc]->title, hash_array->movie[loc]->year,	hash_array->movie[loc]->run_time, 
		hash_array->movie[loc]->average_rating, hash_array->movie[loc]->num_votes, 
		hash_array->movie[loc]->genre
	);
}