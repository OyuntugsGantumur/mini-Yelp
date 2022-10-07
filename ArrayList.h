#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdbool.h>
#include <string.h>
#include "restaurant.h"

/**
 * ArrayList is a data structpure used to store the list of Restaurants in an array.
 */
typedef struct { 
    int num_elements;
    int size;
    Restaurant** resptr;
} ArrayList;     

/**
 * Creates an empty ArrayList
 * @return: pointer to the new ArrayList object
 */
extern ArrayList* createArrayList();

/**
 * Adds the restaurant into the ArraList
 * @param list: pointer to an ArrayList
 * @param restrnt: pointer to the Restaurant to be inserted 
 */
extern void addInArray(ArrayList* list, Restaurant* restrnt);

/**
 * Converts the content of the ArrayList to a string
 * @param list: ArrayList to be printed
 * @return pointer to a string 
 */
extern char* printArray (ArrayList* list);

/**
 * Searches a Restaurant with the specified name and city in the ArrayList
 * @param arr: ArrayList to search
 * @param name: name of the Restaurant being searched
 * @param city: city of the Restaurant being searched
 * @return a pointer to the Restaurant found
 */
extern Restaurant* searchRestaurant(ArrayList* arr, char* name, char* city);

/**
 * Removes the given Restaurant from the ArrayList
 * @param arr: ArrayList pointer
 * @param rest: Restaurant to be deleted
 */
extern void removeFromArray(ArrayList* arr, Restaurant* rest);

/**
 * Frees the ArrayList along with all Restaurants in the ArrayList
 * @param arr: ArrayList to be freed
 */
extern void freeAL(ArrayList* arr);

#endif