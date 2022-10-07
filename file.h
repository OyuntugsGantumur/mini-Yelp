#ifndef FILE_H
#define FILE_H

#include "BinaryTree.h"

/**
 * The File class reads the text file, creates new Restaurants for each block of text, and 
 * adds them to the general list of Restaurants.
 */

/**
 * Reads the text file and creates the objects and puts them in the BinaryTree
 * @param bt: BinaryTree to populate
 * @param btType: the type of the BinaryTree
 */
void readFile(BinaryTree* bt, char* btType);

/**
 * Writes the BinaryTree information to a file
 * @param bt: BinaryTree to write
 */
extern void writeFile(BinaryTree* bt);

/**
 * Trims the whitespace at the end of the string
 * @param str: string to trim
 */
extern void trim(char* str);

/**
 * Divides the string to its food types
 * @param type: string which contains all food types
 * @param food_type: the food types of the Restaurant
 * @param splitter: string to split the type by
 */
extern void divideFoodType(char* type, char** food_type, char* splitter);

/**
 * Divides the string of the hours by days, opening and closing times
 * @param hours: a string with all information about the hours
 * @param week_days: the hours of the Restaurant
 * @param splitter: string to split the hours by
 */
extern void divideDayTime(char* hours, char*** week_days, char* splitter);
#endif