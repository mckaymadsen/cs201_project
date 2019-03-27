#ifndef UI_h_
#define UI_h_

void display_start();
void search_hash_UI();

void main_menu_display();
int main_menu_input();

void create_catalog_display(int max_catalog);
int create_catalog_input();

void read_catalog_display(int max_catalog);
int read_catalog_input();

void update_catalog_display();
int update_catalog_input();

void search_hash_display(int max_search);
void search_hash_input();
void add_movie_display();
int select_movie_input(int found);

int dis_input();
int remove_cat_display();



#endif