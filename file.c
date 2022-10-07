#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ArrayList.h"
#include "restaurant.h"
#include "BinaryTree.h"

/**
 * Remove the whitespaces at the end of a string
 * @param str: string to be manipulated
 */
void trim(char* str) {
    int index = -1; 
    int i = 0;

    while(str[i] != '\0') {
        if(str[i] != ' ') {
            index = i;
        }
        i++;
    }

    str[index+1] = '\0';
}

/**
 * Split a string by comma and adds each substring into the food_type which will later be used to create a new Restaurant. 
 * For each food category not added to ArrayOfLL categories, creates a new LinkedList and adds it to the ArrayOfLL
 *
 * @param type: a line read from the file
 * @param food_type: a pointer to an array that contains the food types of Restaurant
 * @param splitter: string to split the string by
 */
void divideFoodType(char* type, char** food_type, char* splitter) {
    char** ptr = food_type;
    char* token = strtok(type, splitter);

    while(token != NULL) {
        trim(token);
        // *ptr = token;
        *ptr = (char*) malloc (10 * sizeof(char));
        char* ptr1 = *ptr;
        strcpy(ptr1, token);

        ptr++;
        token = strtok(NULL, splitter);
    }
}

/**
 * Divides the string, which contains the days and hours of Restaurant, to smaller strings for each day and time and adds them to a 2D array
 * @param hours: line read from the file
 * @param week_days: a pointer to a 2D array which stores the days and the corresponding hours of the Restaurant
 * @param splitter: string to split the string by
 */
void divideDayTime(char* hours, char*** week_days, char* splitter) {
    char*** ptr1 = week_days;
    char* str;
    char* end = strdup(hours);
    char* temp = end;
    int i = 0;
        
    while( (str = strsep(&end, splitter)) != NULL) {
        *ptr1 = (char**) malloc (20 * sizeof(char*));
        **ptr1 = (char*) malloc (10 * sizeof (char));
        
        char* day = strsep(&str, " ");
        if(i > 0) {
            day = strsep(&str, " ");
        }
        ptr1[0][0] = day;

        day = strsep(&str, " ");
        ptr1[0][1] = day;

        day = strsep(&str, " ");
        ptr1[0][2] = day;
        ptr1++;
        i++;
    }
}

/**
 * Reads the file and adds the information to its respective objects
 * Checks if the file is valid. If not, prints an error message. 
 * @param bt: BinaryTree that contains all Restaurants
 * @param btType: specifies the type of the BinaryTree - name or location
 */

void readFile(BinaryTree* bt, char* btType) {
    FILE* file = fopen("restaurants.txt", "r");

    if(file == NULL) {
        printf("ERROR: Could not open file");
        return;
    }
    char* name;
    char* city;
    char* type;
    char* hours;
    char* cost;
    char* rank;
    char* reviews;
    char** food_type;
    int c = getc(file);
  
    while(c != EOF) {
        name = (char*) malloc (50 * sizeof(char));
        city = (char*) malloc (20 * sizeof(char));
        type = (char*) malloc (100 * sizeof(char));
        hours = (char*) malloc (200 * sizeof(char));
        cost = (char*) malloc (10 * sizeof(char));
        rank = (char*) malloc (10 * sizeof(char));
        reviews = (char*) malloc (20 * sizeof(char));

        fgets(name, 50, file);
        fgets(city, 20, file);
        fgets(type, 100, file);
        fgets(hours, 200, file);
        fgets(cost, 10, file);
        fgets(rank, 10, file);
        fgets(reviews, 20, file);

        name[strcspn(name, "\n")] = 0;
        city[strcspn(city, "\n")] = 0;
        type[strcspn(type, "\n")] = 0;
        hours[strcspn(hours, "\n")] = 0;
        cost[strcspn(cost, "\n")] = 0;
        rank[strcspn(rank, "\n")] = 0;
        reviews[strcspn(reviews, "\n")] = 0;

        food_type = (char**) malloc (100 * sizeof (char*));
        divideFoodType(type, food_type, ", ");

        char*** week_days = (char***) malloc (100 * sizeof(char**));
        divideDayTime(hours, week_days, ",");
        
        trim(name);
        trim(city);
        trim(cost);
        Restaurant* rest = initRestaurant(name, city, food_type, week_days, cost, atof(rank), atoi(reviews));

        if(strcmp(btType, "Name") == 0) {
            insertByName(bt, rest);
        } else {
            insertByLocation(bt, rest);
        }
        
        free(type);
        c = getc(file);
        
    }

    fclose(file);
}

/**
 * Write the contents of the BinaryTree to a file
 * @param bt: BinaryTree to write to the file
 */
void writeFile(BinaryTree* bt) {
    FILE* file = fopen("newrestaurants.txt", "w");

    fputs( toStringBinaryTree(bt), file);

    fclose(file);
}