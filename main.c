#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUFFER 100

// Define the structure for a linked list node
typedef struct Node {
    int compCode;
    int suburbCode;
    char *suburbName;
    int year;
    char *stateCode;
    char *stateName;
    char *LGACode;
    char *LGAName;
    double latitude;
    double longitude;
    struct Node *next;
} Node;

typedef struct Dict1 {
    int numEntries;
    Node *head;
} Dict1;

// Function to create a new node
Node* createNode(int compCode, int suburbCode, const char *suburbName, int year,
                 const char *stateCode, const char *stateName,
                 const char *LGACode, const char *LGAName,
                 double latitude, double longitude) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->compCode = compCode;
    newNode->suburbCode = suburbCode;
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

// Function to append a node
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
void readCSV(const char *filename, Dict1 *dict1) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[200];  // Buffer to hold each line from the CSV
    int isFirstLine = 1;

    while (fgets(line, sizeof(line), file)) {
        if (isFirstLine) {
            isFirstLine = 0;
            continue;
        }

        // Temporary buffers for fields
        int compCode, suburbCode, year;
        char suburbName[BUFFER], stateCode[BUFFER], stateName[BUFFER];
        char LGACode[BUFFER], LGAName[BUFFER];
        double latitude, longitude;

        // Read first four fields
        char *rest = line;
        if (sscanf(rest, "%d,%d,%[^,],%d,", &compCode, &suburbCode, suburbName, &year) != 4) {
            fprintf(stderr, "Error: Incorrect format for first four fields.\n");
            continue;
        }

        // Move the pointer to the part of the line after the 4th field
        rest = strchr(rest, ',');
        rest = strchr(rest + 1, ',');
        rest = strchr(rest + 1, ',');
        rest = strchr(rest + 1, ',');
        rest++;  // Move past the comma after the 4th field

        // Extract stateCode and stateName
        if (rest[0] == '"') {
            rest++;  // Skip the opening quote
            char *endQuote = strchr(rest, '"');
            if (endQuote) {
                *endQuote = '\0';  // Null-terminate the string at the closing quote
                strcpy(stateCode, rest);
                rest = endQuote + 2;  // Skip the closing quote and comma
            } else {
                fprintf(stderr, "Error: Missing closing quote for stateCode.\n");
                continue;
            }
        } else {
            char *comma = strchr(rest, ',');
            if (comma) {
                *comma = '\0';
                strcpy(stateCode, rest);
                rest = comma + 1;
            }
        }

        // Read stateName and move the pointer
        if (sscanf(rest, "%[^,],", stateName) != 1) {
            fprintf(stderr, "Error: Incorrect format for stateName.\n");
            continue;
        }

        // Move to the next field after stateName
        rest = strchr(rest, ',');
        rest++;  // Skip past the comma

        // Extract LGACode
        if (rest[0] == '"') {
            rest++;  // Skip the opening quote
            char *endQuote = strchr(rest, '"');
            if (endQuote) {
                *endQuote = '\0';  // Null-terminate the string at the closing quote
                strcpy(LGACode, rest);
                rest = endQuote + 2;  // Skip the closing quote and comma
            } else {
                fprintf(stderr, "Error: Missing closing quote for LGACode.\n");
                continue;
            }
        } else {
            char *comma = strchr(rest, ',');
            if (comma) {
                *comma = '\0';
                strcpy(LGACode, rest);
                rest = comma + 1;
            }
        }

        // Read LGAName (multiple names in quotes) and move to the next field
        if (rest[0] == '"') {
            rest++;  // Skip the opening quote
            char *endQuote = strchr(rest, '"');
            if (endQuote) {
                *endQuote = '\0';  // Null-terminate the string at the closing quote
                strcpy(LGAName, rest);
                rest = endQuote + 2;  // Skip the closing quote and comma
            } else {
                fprintf(stderr, "Error: Missing closing quote for LGAName.\n");
                continue;
            }
        } else {
            char *comma = strchr(rest, ',');
            if (comma) {
                *comma = '\0';
                strcpy(LGAName, rest);
                rest = comma + 1;
            }
        }

        // Read latitude and longitude
        if (sscanf(rest, "%lf,%lf", &latitude, &longitude) != 2) {
            fprintf(stderr, "Error: Incorrect format for latitude and longitude.\n");
            continue;
        }

        // Create a new node with the parsed data
        Node *newNode = createNode(compCode, suburbCode, suburbName, year,
                                   stateCode, stateName, LGACode, LGAName,
                                   latitude, longitude);

        // Insert the new node into the linked list
        appendNode(dict1, newNode);
    }

    fclose(file);
}

// Function to print list
void printList(Dict1 *dict1) {
    Node *current = dict1->head;
    while (current != NULL) {
        printf("CompCode: %d, SuburbCode: %d, SuburbName: %s, Year: %d, StateCode: %s, StateName: %s, LGACode: %s, LGAName: %s, Latitude: %lf, Longitude: %lf\n",
               current->compCode, current->suburbCode, current->suburbName, current->year,
               current->stateCode, current->stateName, current->LGACode, current->LGAName,
               current->latitude, current->longitude);
        current = current->next;
    }
}

// Function to search records based on the official suburb name
Node* searchRecords(Dict1 *dict1, const char *query) {
    Node *resultsHead = NULL;
    Node *resultsTail = NULL;
    Node *current = dict1->head;

    while (current != NULL) {
        if (strcmp(current->suburbName, query) == 0) {
            Node *newResult = (Node*)malloc(sizeof(Node));
            *newResult = *current;  // Copy node data
            newResult->next = NULL;

            if (resultsHead == NULL) {
                resultsHead = newResult;
                resultsTail = newResult;
            } else {
                resultsTail->next = newResult;
                resultsTail = newResult;
            }
        }
        current = current->next;
    }

    return resultsHead;
}

// Function to write results to a file
void writeResultsToFile(const char *filename, Node *resultsHead) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    Node *current = resultsHead;
    int recordCount = 0;

    while (current != NULL) {
        fprintf(file, "%d,%d,%s,%d,%s,%s,%s,%s,%lf,%lf\n",
                current->compCode, current->suburbCode, current->suburbName,
                current->year, current->stateCode, current->stateName,
                current->LGACode, current->LGAName, current->latitude, current->longitude);
        recordCount++;
        current = current->next;
    }

    if (recordCount == 0) {
        fprintf(file, "NOTFOUND\n");
    }

    fclose(file);
}

// Function to count the number of matching records
int countRecords(Node *resultsHead) {
    int count = 0;
    Node *current = resultsHead;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Function to process queries from stdin
void processQueries(Dict1 *dict1, const char *outputFilename) {
    char query[BUFFER];

    while (fgets(query, sizeof(query), stdin)) {
        // Remove newline character from query
        size_t len = strlen(query);
        if (len > 0 && query[len - 1] == '\n') {
            query[len - 1] = '\0';
        }

        // Search for records
        Node *resultsHead = searchRecords(dict1, query);

        // Write results to file
        writeResultsToFile(outputFilename, resultsHead);

        // Count and print the number of records found
        int recordCount = countRecords(resultsHead);
        printf("Number of records found: %d\n", recordCount);

        // Free memory used for results (Could be useful elsewhere)
        while (resultsHead != NULL) {
            Node *temp = resultsHead;
            resultsHead = resultsHead->next;
            free(temp);
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <csv_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Dict1 *dict1 = (Dict1 *)malloc(sizeof(Dict1));
    if (dict1 != NULL) {
        dict1->numEntries = 0;
        dict1->head = NULL;
    }

    readCSV(argv[1], dict1);
    processQueries(dict1, argv[2]);

    return EXIT_SUCCESS;
}
