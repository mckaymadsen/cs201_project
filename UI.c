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
    printf("\t2. Read a catalog\n");
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

void create_catalog_display(int max_catalog)
{
    printf("\n\tCreate a catalog menu!\n\tThe max size of a catalog is currently set to %d\n", max_catalog);
    printf("\n\tListed below are the available options. A created catalogs will be blank.\n");
    printf("\tOnce a catalog is created, movies can be added using the update catalog option\n");
    printf("\tin the main menu.\n");
    printf("\n\t1. Create a blank catalog\n");
    printf("\t2. Go back \n");
    printf("\n\tEnter 1-2, then press enter: ");
}

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

void read_catalog_display()
{

}

int read_catalog_input()
{
    return -1;
}

void update_catalog_display()
{

}

int update_catalog_input()
{
    return -1;
}

void search_hash_UI()
{
    
}

