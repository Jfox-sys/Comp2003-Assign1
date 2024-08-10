
/* COMP2003 Dictionary Assignment 1
    Gabriel Loh - 1462110, and Z_______ - _______
    11/08/24 */

/*     DATA TYPES:
COMP20003 Code, Official Code Suburb, Year: integers
Longitude, Latitude: doubles
all other fields: strings (may contain spaces and commas)

Special Cases:
Official Code State, Official Code Local Government Area: comma-separated lists of integers (treated as strings for this assignment).
comma-containing strings: enclosed in double quotes ("") within the CSV file,
the quotes are removed when stored in your program according to standard CSV rules.
Suburbs might be in multiple local governments areas and multiple states. This is why the fields Official Code State
and Official Code Local Government Area are not classified as integers. Each of these fields is actually a comma-separated list of integers. For the purposes of this assignment, it is fully sufficient to consider this as a string.
       */

//*******************DEFINITIONS*******************************

#define

//**********************MAIN CODE******************************

/*
    Stage 1 will implement the lookup of data by a given key (Official Name Suburb) and

    Stage 2 will implement the deletion of data by a given key (Official Name Suburb),
    with the remaining data being output after all deletions are finished.\
*/