#ifndef _hash_h_
#define _hash_h_

typedef struct Hash_table
{
	Movie **movie;
    int *empty;
    unsigned int size;
} Hash_table ;


extern Hash_table *newHash_table(unsigned int num_elements);

extern int load_database(Hash_table *hash_array);
extern unsigned long hash_function(char *title);

extern long search_hash(char search_term[50], unsigned long search_results[], Hash_table *hash_array, int max_search);
extern long search_exact_hash(char *search_term, Hash_table *hash_array);

extern void print_hash_location(unsigned long loc, Hash_table *hash_array);

#endif