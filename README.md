# cs201_portfolio_project

This Project is designed to provide CRUD access to the IMBD
movie database (sourced from [IMDB](https://www.imdb.com/interfaces/)).

## Dataset

The specific dataset used can be downloaded from the following link (hosted on UA Box): [LINK HERE](https://alabama.box.com/shared/static/jzs7vasu65euxnp4dbxca543em46pyvb.txt)
or by using the following command:

 "wget -v -O cs201combined_TAB.txt -L https://alabama.box.com/shared/static/jzs7vasu65euxnp4dbxca543em46pyvb.txt"

This dataset combines the "basic" and "ratings" datasets for movies found on IMDB's website. The program will only run on this specific dataset as it contains additional information and has non-movie items removed. MAKE SURE the file is called "cs201combined_TAB.txt" Any other name will not work. A
custom version dataset was chosen due to the added value of having the average ratings and votes included. It is not advantageously sorted as the movies are in the same order as the original data set, with additional information appended.

**Statistics:**
- File Size:   27.6 MB
- Content:     511,709 unique movies
  - Each title contains the following information: 
  - Title 
  - Year Aired 
  - Runtime
  - IMBD Rating 
  - Number of Votes making up the rating 
  - Main Genre
 
 
 ## Operation

 This program operates on the idea of having a current catalog. Movies can be added and removed from this structure.
 The catalog can be save to and load from files using the program. Do not attempt to edit these files.

 A video of the operation is available here: [LINK HERE](https://youtu.be/sU1Od9_yBAo) 
 
 **Setup**

 To get the data file, run the command below: 
 
 "wget -v -O cs201combined_TAB.txt -L https://alabama.box.com/shared/static/jzs7vasu65euxnp4dbxca543em46pyvb.txt". 
 
 
 If, for some reason this doesn't work, the file can be manually downloaded from the link in the Dataset section. 
 The code will only run with this data file.

 To run the program, type "make" in the terminal. To run the program, type "make run" or "./prog". Expect for the database to take ~3 seconds to load.
 A message will appear showing the dataset has been loaded and you can begin using the program.

 **Using the Program**

 All menu choice are done by selecting a number corresponding to an option. There is an option to "Go back" or Exit/Cancel on most menus.
 This will return you to the previous menu or exit the program.

 ***Constraints***
 Currently, the max returned search results for the substring search is set to 15 and the maximum size for the catalog is set to 50.

 ***Tips***

 Make sure you've loaded the catalog you want to edit!
 Do not edit the catalog files/ Editing them will make the program display unexpected behavior and potentially crash.

 ## Discussion of Design Choices
 
 **Data Structure**
 
 The main data structure used was a hash table with quadratic probing and the DJB2 hashing function. This was done to provide a ~O(1) 
 search time when the search term is the Exact title. Quadratic probing was chosen due to the ease of use and to help avoid collisions
 as there are several movies with the same title (i.e there are over 5 movies called "Star").

 Each movie has its data stored in a struct.

 For the user catalog, a simple array of movie struct pointers was chosen due to the small size of the catalogs (<50), although this can be easily increased
 or decreased in the code.

 **Searching**
 
 Two search methods were implemented: 1. an Exact title search and 2. a Substring search.

 ***Exact***
 The exact search is done the exact way the title is initially loaded into the hashtable. If there is a string match, it returns the location. This is done is ~O(1).
 
 ***Substring***
 The search is done with the strstr function in the string.h library. It returns a pointer to the first location of a string in the
 given second string. Because a hash table was used, there is really no way to avoid a linear search when looking for substrings.
 
 
 **Summary**

Looking back, there may have been more efficient data structures for this particular data set. The hash table's advantages are partially negated by the duplicate
keys (movie titles). However, the ~O(1) search time given for exact title searches and the fact that the dataset is not particularly large allows for the hash table
to do its job successfully.


## General
 Tested on a VM running Ubuntu 18.04.2 LTS with 1 processor, 4GB RAM, and 40GB HDD space.


 ## HELP
Contact mmadsen@crimson.ua.edu for help with the issue.
