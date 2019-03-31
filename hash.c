#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "movie.h"
#include "hash.h"


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
void load_database(Hash_table *hash_array)
{
	FILE *fptr;										//create the file opener
	//fptr = fopen("cs201database_TAB.txt", "r");		//open database 
	//fptr = fopen("test_data2.txt", "r");//debug
	fptr = fopen("finalV3.txt", "r");	
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
 * This function searches for string matches in the hash table.
 * The string to be searched for is put into the hash function
 * and the returned index is used as a starting point. This is not
 * a very effiecent searach for partial strings, but will give 
 * close to O(1) results when the exact title is used. 
 */
long search_hash(char *search_term, unsigned long search_results[], Hash_table *hash_array, int max_search)
{
	//ADD EXACT SEARCH
    
    int start_index = hash_function(search_term) % hash_array->size;
	int index = start_index;
	int searched = 0;
	int found = 0;

	while ((found < max_search) && (searched < hash_array->size)) 
	{
		char *pch = strstr(hash_array->movie[index]->title, search_term);
		if ( pch != NULL) 		//if matching substirng is found
		{			
			search_results[found] = hash_array->movie[index]->location;
			
			found++;
		}	

		
		index++;
		index %= hash_array->size;

		searched++;
	}
	//printf("%d",found);
	if (searched == 0)	return -1;

	//printf("%d", found);//debug
	//printf("\t%d", searched);

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


void print_hash_location(unsigned long loc, Hash_table *hash_array)
{
	printf("\t%-30.30s\t%d\t%s\t\t%.2f\t%d\t%s\n",
		hash_array->movie[loc]->title, hash_array->movie[loc]->year,	hash_array->movie[loc]->run_time, 
		hash_array->movie[loc]->average_rating, hash_array->movie[loc]->num_votes, 
		hash_array->movie[loc]->genre
	);
}