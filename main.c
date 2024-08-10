
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

// Define the structure for a linked list node
typedef struct Node {
    int COMP20003Code;             // The record IDs added by the COMP20003 teaching team (integer)
    int officialCodeSuburb;        // The suburb ID (integer)
    char officialNameSuburb[20];   // The name of the suburb (string)
    int Year;                      // The year the information was recorded for (integer)
    char officialCodeState[20];    // The IDs of the corresponding states (string)
    char officialNameState[20];    // The names of the corresponding states (string)
    char officialCLGA[20];         // The IDs of the corresponding code (of) local government areas (string)
    char officialNLGA[20];         // The names of the corresponding name (of) local government areas (string)
    double Latitude;                            - The latitude (y) of the suburb centre (double)
    double Longitude;
    struct Node *next;
} Node;

//**********************MAIN CODE******************************

//Function to create a new node:
Node* createNode(//INSERT NECESSARY VARIABLES HERE) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    //INSERT CODE HERE
    newNode->next = NULL;
    return newNode;
}

//Function to append a node:
void appendNode(Node **head, //INSERT NECESSARY VARIABLES HERE) {
    Node *newNode = createNode(id, name, score);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

//Function to read csv into list:
void readCSVIntoList(Node **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        //INSERT CODE HERE
        /* FOR EXAMPLE
        int id;
        char name[50];
        double score; */

        // Parse the line into fields
        sscanf(line, "%d,%49[^,],%lf", &id, name, &score);

        // Add the data to the linked list
        appendNode(head, id, name, score);
    }

    fclose(file);
}

//Function to print list:

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf(//INSERT DECLARATIONS HERE);
        current = current->next;
    }
}

/*
    Stage 1 will implement the lookup of data by a given key (Official Name Suburb) and

    Stage 2 will implement the deletion of data by a given key (Official Name Suburb),
    with the remaining data being output after all deletions are finished.\
*/