# cs201_portfolio_project

This Project is designed to provide CRUD access to the IMBD
movie database (sourced from [IMDB](https://www.imdb.com/interfaces/)).

## Dataset

The specific dataset used can be downloaded from the following link (hosted on UA Box): [LINK HERE](https://alabama.box.com/s/1v5z0nt0nspobdxqcgw590mvelbg4xiq)

This datset combines the "basic" and "ratings" datasets found on IMDB's website.

**Statistics:**
- File Size:   30.8MB (30,769,945 bytes)
- Content:     511,709 unique movies
  - Each title contains the following information: 
  - Title 
  - Year Aired 
  - Runtime
  - IMBD Rating 
  - Number of Votes making up the rating 
  - Main Genre
 
 
 ## Operation
 
 **Setup**

 To get the data file, run the command below: 
 
 "wget -v -O cs201database_TAB.txt -L https://alabama.box.com/shared/static/1v5z0nt0nspobdxqcgw590mvelbg4xiq.txt". 
 
 If, for some reason
 this doesnt work, the file can be manually downloaded from the link about in the Dataset section.

 To run the program, type "make" in the terminal. To run the program, type "./prog". Expect for the database to take aobut 15 seconds to load.
 A message will appear showing the dataset has been loaded and you can begin using the program.

 **Using the Program**

 All menu choice are done by selecting a number corresponding to an option. THere is an option to "Go back" or "Exit" each menu.
 This will return you to the previous menu or exit the program.

 ***Tips***

 Make sure you've loaded the catalog you want to edit!

 ## Dicussion of Design Choices
 
 **Data Structure**
 The main data structure used was a hash table with linear probing and the DJB2 hashig function. This was done to provide a ~O(1) 
 search time when the search term is the Exact title. Quadatric probing was chosen due to the ease of use and to help avoid collisons
 as tehre are several movies with the same title (i.e there are over 5 movies called "Star").

 Each movie has its data stored in a struct.

 For the user catalog, a simple array was chosen due to the small size of the catalogs (<50), although this can be easily increased
 or decreaed in the code.

 **Searching**
 The search is done with the strstr function in the string.h library. It returns a pointer to the first location of a string in the
 given second string. Becuase a hash table was used, there is really no way to avoid a linear search when looking for substrings.
 However, given the O(1) time for a Exact Title search and the increased search ability, this was deemed acceptable. 


 
 ### Tips
 TODO
 
 ## HELP
 TODO
