#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "restaurant.h"
 

/**
 * Create a new Restaurant with the given parameters
 * @return: a pointer to the newly created Restaurant 
 */
Restaurant* initRestaurant(char* name, char* city, char** type, char*** hours, char* cost, float rank, int reviews) {
    Restaurant* rest = (Restaurant*) malloc (sizeof (Restaurant));

    rest->name = name; 
    rest->city = city;
    rest->cost = cost;
    rest->rank = rank;
    rest->reviewers = reviews;
    rest->categories = type;
    rest->hours = hours;

    return rest;
}

/**
 * Converts the Restaurant information into a string
 * @param r: Restaurant to be printed
 * @return: a pointer to the string
 */
char* printRestaurant(Restaurant r) {
    char* buffer = (char*) malloc (300 * sizeof (char));
    char* work_hour = (char*) malloc (150 * sizeof(char));
    char* food_type = (char*) malloc (50 * sizeof(char));
    int i = 0;
    while(i < 7) {
        if(r.hours[i] != NULL) {
           
            if(i == 0) {
                strcpy(work_hour, r.hours[i][0]);
            } else {
                strcat(work_hour, r.hours[i][0]);
            }

            strcat(work_hour, " ");
            strcat(work_hour, r.hours[i][1]);
            strcat(work_hour, " ");
            strcat(work_hour, r.hours[i][2]);
            strcat(work_hour, " ");
        }
        
        i++;
    }

    i = 0;
    while(r.categories[i] != NULL) {
        
        if(i == 0) {
            strcpy(food_type, r.categories[i]);
        } else {
            strcat(food_type, r.categories[i]);
        }
        
        strcat(food_type, " ");
        i++;
    }

    sprintf(buffer, "%s \n%s \n%s \n%s \n%s \n%3.1f \n%d\n", r.name, r.city, food_type, work_hour, r.cost, r.rank, r.reviewers);
    return buffer;
}

/**
 * Frees the Restaurant object from the memory
 * @param: Restaurant to be freed
 */
void freeRestaurant(Restaurant* rest) {
    free(rest->name);
    free(rest->cost);
    free(rest->city);

    for(int i = 0; i < 3 && rest->categories[i] != NULL; i++) {
        free(rest->categories[i]);
    }
    free(rest->categories);

    for(int i = 0; i < 7 && rest->hours[i] != NULL; i++) {
        free(rest->hours[i]);
    }

    free(rest->hours);
    free(rest);
}