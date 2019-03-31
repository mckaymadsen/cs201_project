/*  Filename:       UI.c
 *  Author:         McKay Madsen
 *  Updated:        3/25/19
 *  Description:
 *      Contains display functions and input getters for the portfolio project
 *      Each one prompts for input and loops until valid input is received or and
 *      Exit condition has been reached.
 */

#include <stdio.h>
#include <string.h>
#include "UI.h"


/* 
 * Displays the program start text to the terminal
 */
void display_start()
{
    printf("\n\n");
    printf("\tCS 201 - Spring 2018 - Portfolio Project\n");
    printf("\tCreated By: McKay Madsen\n\n");
    printf("\tThis program provides CRUD access to the IMDB movie database\n");
    printf("\tPlease refer to the GitHub for instructions and read the README before use.\n");
    printf("\n\tThis program operates on the idea of a current catalog. All changes are made to this");
    printf("\n\tand these changes can be saved to a file. The current catalog can also be loaded from");
    printf("\n\tone of these files\n\tHave fun!");

    return;
}

/* 
 * Displays the main menu text to the terminal
 */
void main_menu_display()
{
    printf("\n\tChoose an Action:\n\n");
    printf("\t1. Create a blank catalog / Clear current catalog -- creates a blank file or clears the current catalog\n");
    printf("\t2. Read/Load a catalog  -- options to load or display an existing catalog and save the current catalog\n");
    printf("\t3. Update the contents of the current catalog -- add or remove movies, save catalog\n");
    printf("\t4. Remove a catalog file -- delete a catalog file\n");
    printf("\t5. Exit\n");
    printf("\n\tEnter 1 - 5, and then press enter: ");
}

/* 
 * This function gets the user input from the main menu prompt. It returns 0 by default
 * for error checking, -1 if "Exit" or 5 is entered, or 1-4 correspoding to a menu prompt.
 * fgets() is used to read in the input until a new line is reached or BUFSIZE (8216)
 * is hit. sscanf is used to pull the formatted input The function will then check the
 * input and reprompt until a valid input (1-4 or "Exit") is entered.
 */
int main_menu_input()
{
    int valid_input = 0;
	int choice = 0;

    char buf[BUFSIZ];

    fgets(buf, BUFSIZ, stdin);
    while (!valid_input) 
    {
        if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 5 ))
        {
                valid_input = 1;
                return choice;
        }
        else if (strcmp(buf,"Exit\n") == 0 || choice == 5)
        {
            return -1;
        }
        else
        {     
            printf("\n\t\tInvlaid Input, please try again. Type \"Exit\" to quit: ");
            fgets(buf, BUFSIZ, stdin);
            if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 5 ))
            {
                valid_input = 1;
                return choice;
            } 
        }        
    }

    return 0;
}

/* 
 * Displays the create catalog menu text to the terminal
 */
void create_catalog_display(int max_catalog)
{
    printf("\n\tCreate a blank catalog menu!\n\tThe max size of a catalog is currently set to %d\n", max_catalog);
    printf("\n\tListed below are the available options. A created catalog will be blank.\n");
    printf("\tOnce a catalog is created, movies can be added using the update catalog option\n");
    printf("\tin the main menu.\n");
    printf("\n\t1. Create a blank catalog file\n");
    printf("\t2. Clear current catalog \n");
    printf("\t3. Go back");
    printf("\n\tEnter 1-3, then press enter: ");
}

/*
 * Reads in user input to determine choice for the create catalog menu.
 * A 1 creates a catalog and a 2 goes back to the previous menu.
 */
int create_catalog_input()
{
    int valid_input = 0;
	int choice = 0;

    char buf[BUFSIZ];

    fgets(buf, BUFSIZ, stdin);
    while (!valid_input) 
    {
        if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 4 ))
        {
                valid_input = 1;
                return choice;
        }
        else if (strcmp(buf,"Exit\n") == 0)
        {
            return -1;
        }
        else
        {     
            printf("\n\n\tInvlaid Input, please try again. Type \"Exit\" to quit: ");
            fgets(buf, BUFSIZ, stdin);
            if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 4 ))
            {
                valid_input = 1;
                return choice;
            } 
        }        
    }

    return 0;
}

/*
 * Display driver for read catalog function
 */
void read_catalog_display(int max_catalog)
{
    printf("\n\tRead/Load a catalog menu!\n\tThe max size of a catalog is currently set to %d\n", max_catalog);
    printf("\n\tListed below are the available options. The selected catalog can only be read from this screen\n");
    printf("\tTo edit the catalog, go to the main menu and chose \"Update Catalog\"\n");
    printf("\n\t1. Display an existing catalog");
    printf("\n\t2. Display the current catalog");
    printf("\n\t3. Load an existing catalog");
    printf("\n\t4. Save the current catalog");
    printf("\n\t5. Go back \n");
    printf("\n\tEnter 1-5, then press enter: ");
}

/*
 * Input getter for read catalog function
 */
int read_catalog_input()
{
    int valid_input = 0;
	int choice = 0;

    char buf[BUFSIZ];

    fgets(buf, BUFSIZ, stdin);
    while (!valid_input) 
    {
        if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 6 ))
        {
                valid_input = 1;
                return choice;
        }
        else if (strcmp(buf,"Exit\n") == 0)
        {
            return -1;
        }
        else
        {     
            printf("\n\n\tInvlaid Input, please try again. Type \"Exit\" to quit: ");
            fgets(buf, BUFSIZ, stdin);
            if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 6 ))
            {
                valid_input = 1;
                return choice;
            } 
        }        
    }

    return 0;
}

/*
 * Display driver for update catalog function
 */
void update_catalog_display(int max_catalog)
{
    printf("\n\tUpdate a catalog menu!\n\tThe max size of a catalog is currently set to %d\n", max_catalog);
    printf("\n\tListed below are the available options. Make sure to load/save your catalog!\n");
    printf("\n\t1. Dislpay current catalog\n");
    printf("\t2. Add movie to current catalog \n");
    printf("\t3. Delete movie from current catalog \n");
    printf("\t4. Save the current catalog\n");
    printf("\t5. Go back \n");
    printf("\n\tEnter 1-5, then press enter: ");
}

/*
 * Input getter for update catalog function
 */
int update_catalog_input()
{
    int valid_input = 0;
	int choice = 0;

    char buf[BUFSIZ];

    fgets(buf, BUFSIZ, stdin);
    while (!valid_input) 
    {
        if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 6 ))
        {
                valid_input = 1;
                return choice;
        }
        else if (strcmp(buf,"Exit\n") == 0)
        {
            return -1;
        }
        else
        {     
            printf("\n\n\tInvlaid Input, please try again. Type \"Exit\" to quit: ");
            fgets(buf, BUFSIZ, stdin);
            if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 6 ))
            {
                valid_input = 1;
                return choice;
            } 
        }        
    }
    
    return -1;
}

/*
 * Display driver for search hash function
 */
void search_hash_display(int max_search)
{
    printf("\n\tSearch for a movie!\n");
    printf("\n\tTo search for a movie, enter the seach string below.\n");
    printf("\tThis string is case-sesnstive and may take some time to complete.\n");
    printf("\tThe max number of returned results is set to %d\n", max_search);
    printf("\tTo get more results, refine your search\n");
    printf("\n\tEnter search term (min of 3 characters, max of 150 characters): ");
}

/*
 * Input getter for update catalog function
 */
int search_hash_choice()
{
    int valid_input = 0;
	int choice = 0;

    char buf[BUFSIZ];

    fgets(buf, BUFSIZ, stdin);
    while (!valid_input) 
    {
        if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 3 ))
        {
                valid_input = 1;
                return choice;
        }
        else if (strcmp(buf,"Cancel\n") == 0)
        {
            return -1;
        }
        else
        {     
            printf("\n\n\tInvlaid Input, please try again. Type \"Cancel\" to quit: ");
            fgets(buf, BUFSIZ, stdin);
            if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 3 ))
            {
                valid_input = 1;
                return choice;
            } 
        }        
    }
    
    return -1;
}

/*
 * Display driver for exact search
 */
void search_exact_hash_display()
{
    printf("\n\tSearch for an exact movie!\n");
    printf("\n\tEnter the movie title (case sensitive): ");
}

/*
 * Input getter for the select movie 
 */
int select_movie_input(int found)
{
    int valid_input = 0;
	int choice = 0;

    char buf[BUFSIZ];

    printf("\n\tEnter the number of the movie listed above (1 to %d) or \"Cancel\" to add a movie: ", found);
    fgets(buf, BUFSIZ, stdin);
    while (!valid_input) 
    {
        if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < found+1 ))
        {
                valid_input = 1;
                return choice;
        }
        else if (strcmp(buf,"Cancel\n") == 0)
        {
            return -1;
        }
        else
        {     
            printf("\n\n\tInvalid choice\n");
            printf("\tPlease enter a number from (1 to %d) or \"Cancel\" to quit: ", found);
            fgets(buf, BUFSIZ, stdin);
            if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < found+1 ))
            {
                valid_input = 1;
                return choice;
            } 
        }        
    }
    
    return -1;
}

/*
 * Display driver and input getter for the distribution chioce in the add movie function
 */
int dis_input()
{
    int valid_input = 0;
	int choice = 0;

    char buf[BUFSIZ];

    printf("\n\tPlease select a distrbuition method by entering the corresponding number.");
    printf("\n\tEnter \"Cancel\" to quit.");
    printf("\n\t1. BluRay   2. DVD   3. Digital \n\tEnter choice: ");
    fgets(buf, BUFSIZ, stdin);
    char *p = strrchr(buf, '\n');  	//removes trailing newline 
	if (p != NULL) *p = '\0';

    while (!valid_input) 
    {
        if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 4 ))
        {
                valid_input = 1;
                return choice;
        }
        else if (strcmp(buf,"Cancel\n") == 0)
        {
            return -1;
        }
        else
        {     
            printf("\n\n\tInvalid choice\n");
            printf("\tPlease enter a number from (1 to 3) or \"Cancel\" to quit: ");
            fgets(buf, BUFSIZ, stdin);
            if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 4))
            {
                valid_input = 1;
                return choice;
            } 
        }        
    }
    
    return -1;
}

/*
 * Dispaly driver for the remove Catalog Menu. 
 */
int remove_cat_display(int cat_size)
{
    int valid_input = 0;
	int choice = 0;

    char buf[BUFSIZ];

    printf("\n\tEnter the movie number you'd like to remove.");
    printf("\n\tEnter \"Cancel\" to quit. ");

    fgets(buf, BUFSIZ, stdin);
    while (!valid_input) 
    {
        if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < cat_size+1 ))
        {
                valid_input = 1;
                return choice;
        }
        else if (strcmp(buf,"Cancel\n") == 0)
        {
            return -1;
        }
        else
        {     
            printf("\n\n\tInvalid choice\n");
            printf("\tPlease enter a number from (1 to %d) or \"Cancel\" to quit: ", cat_size+1);
            fgets(buf, BUFSIZ, stdin);
            if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < cat_size+1))
            {
                valid_input = 1;
                return choice;
            } 
        }        
    }
    
    return -1;
}

