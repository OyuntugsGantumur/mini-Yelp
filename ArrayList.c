#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ArrayList.h"

/**
 * Create a new ArrayList with 0 elements and an array of length 0
 * @return a pointer to a newly created ArrayList
 */
ArrayList* createArrayList() {
    ArrayList* list = (ArrayList*) malloc( sizeof( ArrayList ));
    list->num_elements = 0;
    list->size = 0;
    list->resptr = NULL;
    return list;
}

/**
 * Add a Restaurant to the ArrayList. If the ArrayList is full, then create a new array with doubled the size
 * @param list: a pointer to the ArrayList
 * @param restrnt: a pointer to the Restaurant to be inserted after the last known element
 */
void addInArray(ArrayList* list, Restaurant* restrnt) {
    
    if(list->size == 0) {  

        list->resptr = (Restaurant**) malloc (10 * sizeof (Restaurant*));
        *(list->resptr) = restrnt;
        list->size = 10;
        list->num_elements++;

    } else if(list->num_elements < list->size) {

        list->resptr [list->num_elements] = restrnt;
        list->num_elements++;

    } else if(list->num_elements == list->size){

        Restaurant** temp = list->resptr;
        int old_size = list->size;
        int new_size = 2 * old_size;
        list->resptr = (Restaurant**) malloc (new_size * sizeof (Restaurant*));

        for(int i = 0; i < list->size; i++) {
            list->resptr[i] = *temp;
            temp++;
        }

        list->resptr [list->num_elements] = restrnt;
        list->num_elements++;
        list->size = new_size;
    }
}

/**
 * Copies num Restaurants from the source to the destination 
 * @param src: the source of the Restaurants to copy from
 * @param dest: the destination to paste
 * @param num: the number of Restaurants to be copied
 */
void copyData( Restaurant** src, Restaurant** dest, int num ) {
  for( int i = 0; i < num; i++ ) {
    *dest = *src;
    src++;
    dest++;
  }
}

/**
 * Removes the specified Restaurant from the ArrayList and adjusts all the remaining Restaurants
 * @param arr: the ArrayList to delete from
 * @param rest: the Restaurant to be deleted
 */
void removeFromArray(ArrayList* arr, Restaurant* rest) {
    int index = 0;
    Restaurant** temp = arr->resptr;
    Restaurant** temp1 = arr->resptr;

    for(int i = 0; i < arr->num_elements; i++) {
        if(strcmp(arr->resptr[i]->name, rest->name) == 0 && strcmp(arr->resptr[i]->city, rest->city) == 0 ) {
            temp++;
            copyData(temp, temp1, arr->num_elements-index-1);
            arr->num_elements--;
            return;
        }

        temp++;
        temp1++;
        index++;
    }
}

/**
 * Converts the contents of the ArrayList to a string - calls printRestaurant to print each Restaurant
 * @param list: a pointer an ArrayList to be printed
 * @return: a pointer to the string 
 */
char* printArray (ArrayList* list) {
    char* s = (char*) malloc ((list->num_elements * 400) * sizeof(char) );

    if(list->size > 0) {

        for(int i = 0; i < list->num_elements; i++) {
            sprintf(&s[strlen(s)], "%s\n", printRestaurant( *(list->resptr[i]) ));
        }

    } else {
        strcat(s, "List is empty!");
    }

    return s;
}

/**
 * Searches for a Restaurant matching with the given name and city in the ArrayList. Returns null if no Restaurant is found.
 * @param arr: Arraylist to search in 
 * @param name: name of the Restaurant to search for
 * @param city: city of the Restaurant to search for
 * @return: a pointer to the matching Restaurant
 */
Restaurant* searchRestaurant(ArrayList* arr, char* name, char* city) {
    for(int i = 0; i < arr->num_elements; i++) {
        if(strcmp(arr->resptr[i]->name, name) == 0 && strcmp(arr->resptr[i]->city, city) == 0) {
            return arr->resptr[i];
        }
    }

    return (Restaurant*)NULL;
}

/**
 * Frees the memory of the ArrayList and the Restaurants it contains
 * @param arr: ArrayList to free
 */
void freeAL(ArrayList* arr) {

    for(int i = 0; i < arr->num_elements; i++) {
        freeRestaurant(arr->resptr[i]);
    }

    free(arr->resptr);
    free(arr);
}