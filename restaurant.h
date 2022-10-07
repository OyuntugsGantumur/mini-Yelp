#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string.h>
#include <stdbool.h>

/**
 * @struct Restaurant stores the name, city, food categories, hours, cost, rate, and the number of reviewers for each restaurant.
 */
typedef struct {
    char* name;
    char* city;
    char** categories;
    char*** hours;
    char* cost;
    float rank;
    int reviewers;
} Restaurant;

/**
 * Creates a Restaurant object
 * @param name: name of the Restaurant
 * @param city: city of the Restaurant
 * @param type: types of food the Restaurant serves
 * @param hours: hours of the Restaurant
 * @param cost: cost - $, $$, $$$
 * @param rank: rate of the Restaurant
 * @param reviews: number of reviews
 * @return: Restaurant object
 */
extern Restaurant* initRestaurant(char* name, char* city, char** type, char*** hours, char* cost, float rank, int reviews);

/**
 * Converts the Restaurant information into a string
 * @param r: Restaurant to print
 * @return: a pointer to the string
 */
extern char* printRestaurant(Restaurant r);

/**
 * Frees the memory of the Restaurant
 * @param rest: Restaurant to free
 */
extern void freeRestaurant(Restaurant* rest);

#endif
