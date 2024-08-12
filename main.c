
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Define the structure for a linked list node
typedef struct Node {
    int compCode;             // The record IDs added by the COMP20003 teaching team (integer)
    int suburbCode;        // The suburb ID (integer)
    char *suburbName;   // The name of the suburb (string)
    int year;                      // The year the information was recorded for (integer)
    char *stateCode;    // The IDs of the corresponding states (string)
    char *stateName;    // The names of the corresponding states (string)
    char *LGACode;         // The IDs of the corresponding code (of) local government areas (string)
    char *LGAName;         // The names of the corresponding name (of) local government areas (string)
    double latitude;                            - The latitude (y) of the suburb centre (double)
    double longitude;
    struct Node *next;
} Node;

typedef struct Dict1 {
    int numEntries;
    Node *head;
} Dict1;



Dict1 *dict1 = (Dict1 *)malloc(sizeof(Dict1));
if (dict1 != NULL) {
    dict1->numEntries = 0;   // Initialize the number of entries to 0
    dict1->head = NULL;      // Initialize the head pointer to NULL
}

//**********************MAIN CODE******************************

//Function to create a new node:
Node* createNode(int compCode, int suburbCode, const char *suburbName, int year,
                 const char *stateCode, const char *stateName,
                 const char *LGACode, const char *LGAName,
                 double latitude, double longitude) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->compCode = compCode;
    newNode->suburbCode = suburbCode;

    // Allocate memory for and copy strings
    newNode->suburbName = strdup(suburbName);
    newNode->year = year;
    newNode->stateCode = strdup(stateCode);
    newNode->stateName = strdup(stateName);
    newNode->LGACode = strdup(LGACode);
    newNode->LGAName = strdup(LGAName);

    newNode->latitude = latitude;
    newNode->longitude = longitude;
    newNode->next = NULL;

    return newNode;
}

//Function to append a node:
void appendNode(Dict1 *dict1, Node *newNode) {
    if (dict1->head == NULL) {
        dict1->head = newNode;
    } else {
        Node *current = dict1->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to read data from CSV into linked list
void readCSV(const char *filename, Node **head, Dict1 *dict1) {
     FILE *file = fopen(filename, "r");

     // Check if the file was successfully opened
     if (!file) {
         perror("Error opening file");
         exit(EXIT_FAILURE);
     }

     char line[512];  // Buffer to hold each line from the CSV
     int isFirstLine = 1;  // Flag to skip the header line

     // Read the file line by line
     while (fgets(line, sizeof(line), file)) {
         // Skip the first line (header)
         if (isFirstLine) {
             isFirstLine = 0;
             continue;
         }

         // Create variables to hold each field from the CSV
         int compCode, suburbCode, year;
         char suburbName[128], stateCode[128], stateName[128];
         char LGACode[128], LGAName[128];
         double latitude, longitude;

         // sscanf reads and parses the line according to the expected format
         sscanf(line, "%d,%d,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%lf,%lf",
                &compCode, &suburbCode, suburbName, &year, stateCode,
                stateName, LGACode, LGAName, &latitude, &longitude);

         // Create a new node with the parsed data
         Node *newNode = createNode(compCode, suburbCode, suburbName, year,
                                    stateCode, stateName, LGACode, LGAName,
                                    latitude, longitude);

         // Insert the new node at the beginning of the linked list
         appendNode(dict1, newNode)
     }

     // Close the file after reading
     fclose(file);
 }


//Function to print list:

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("CompCode: %d, SuburbCode: %d, SuburbName: %s, Year: %d, StateCode: %s, StateName: %s, LGACode: %s, LGAName: %s, Latitude: %lf, Longitude: %lf\n",
               current->compCode, current->suburbCode, current->suburbName, current->year,
               current->stateCode, current->stateName, current->LGACode, current->LGAName,
               current->latitude, current->longitude);
        current = current->next;
    }
}

/*
    Stage 1 will implement the lookup of data by a given key (Official Name Suburb) and

    Stage 2 will implement the deletion of data by a given key (Official Name Suburb),
    with the remaining data being output after all deletions are finished.\
*/