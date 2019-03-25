/*  Filename:       UI.c
 *  Author:         McKay Madsen
 *  Date:           3/15/19
 *  Description:
 *      Contains display functions and input getters for the portfolio project
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
    printf("\tPlease refefer to the GitHub for instructions");

    printf("\n");

    return;
}

/* 
 * Displays the main menu text to the terminal
 */
void main_menu_display()
{
    printf("\n\tChoose an Action:\n\n");
    printf("\t1. Create a new catalog\n");
    printf("\t2. Read/Load a catalog\n");
    printf("\t3. Update a catalog\n");
    printf("\t4. Remove a catalog\n");
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
    printf("\n\tCreate a catalog menu!\n\tThe max size of a catalog is currently set to %d\n", max_catalog);
    printf("\n\tListed below are the available options. A created catalog will be blank.\n");
    printf("\tOnce a catalog is created, movies can be added using the update catalog option\n");
    printf("\tin the main menu.\n");
    printf("\n\t1. Create a catalog\n");
    printf("\t2. Go back \n");
    printf("\n\tEnter 1-2, then press enter: ");
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
        if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 3 ))
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
            if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < 3 ))
            {
                valid_input = 1;
                return choice;
            } 
        }        
    }

    return 0;
}

void read_catalog_display(int max_catalog)
{
    printf("\n\tRead/Load a catalog menu!\n\tThe max size of a catalog is currently set to %d\n", max_catalog);
    printf("\n\tListed below are the available options. The selected catalog can only be read from this screen\n");
    printf("\tTo edit the catalog, go to the main menu and chose \"Update Catalog\"\n");
    printf("\n\t1. Display an existing catalog");
    printf("\n\t2. Display the current catalog");
    printf("\n\t3. Load an existing catalog");
    printf("\n\t4. Save the current catalog\n");
    printf("\t5. Go back \n");
    printf("\n\tEnter 1-5, then press enter: ");
}

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

void search_hash_display(int max_search)
{
    printf("\n\tSearch for a movie!\n");
    printf("\n\tTo search for a movie, enter the seach string below.\n");
    printf("\tThis string is case-sesnstive and may take some time to complete.\n");
    printf("\tThe max number of returned results is set to %d\n", max_search);
    printf("\tTo get more results, refine your search\n");
    printf("\n\tEnter search term (max of 150 characters): ");
}

void search_hash_input()
{

}

void add_movie_display()
{

}

int select_movie_input(int found)
{
    int valid_input = 0;
	int choice = 0;

    char buf[BUFSIZ];

    printf("\n\tEnter the number of the movies listed above (1 to %d): ", found);
    fgets(buf, BUFSIZ, stdin);
    while (!valid_input) 
    {
        if ((sscanf(buf, "%d", &choice) == 1) && (choice > 0 && choice < found+1 ))
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
            printf("\n\n\tInvalid choice\n");
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

