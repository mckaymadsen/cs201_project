#ifndef _catalog_h_
#define _catalog_h_

typedef struct Catalog
{
	Movie **movie;
    unsigned int size;
    unsigned int capacity;
}Catalog;

extern Catalog *newCatalog(unsigned int max_catalog);

extern int create_catalog(void);

extern int open_catalog(int load_flag, Catalog *current_catalog);

extern void load_catalog(char *filename, Catalog *current_catalog);
extern void display_catalog(Catalog *current_catalog);

extern void delete_movie(Catalog *current_catalog);

extern void save_catalog(Catalog *current_catalog);
extern int remove_catalog(void);


#endif