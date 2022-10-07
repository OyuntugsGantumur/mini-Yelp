#ifndef BINARYTREE
#define BINARYTREE
#include "restaurant.h"
#include "ArrayList.h"

/**
 * @struct BTNode creates a binary tree node which holds an ArrayList of Restaurants with the same location or the same name
 */
typedef struct BTNode {
    struct BTNode* right;
    struct BTNode* left;
    ArrayList* arr;
    char* name;
} BTNode;

/**
 * @struct BinaryTree creates a binary tree
 */ 
typedef struct BinaryTree {
    BTNode* root;
    int size;
} BinaryTree;

/**
 * Creates an empty BinaryTree
 * @return: a pointer to BinaryTree object
 */
extern BinaryTree* createBinaryTree();

/**
 * Inserts a Restaurant into the BinaryTree by its name
 * @param bt: BinaryTree to add the Restaurant
 * @param rest: Restaurant to insert
 */
extern void insertByName(BinaryTree* bt, Restaurant* rest);

/**
 * Inserts a Restaurant into the BinaryTree by its location
 * @param bt: BinaryTree to add the Restaurant in
 * @param rest: Restaurant to insert
 */
extern void insertByLocation(BinaryTree* bt, Restaurant* rest);

/**
 * Searches for BTNode with the given name or city recursively
 * @param parent: the current BTNode
 * @param name: name to search for
 * @param city: city to search for
 * @return: a pointer to a matching BTNode
 */
extern BTNode* searchRecursive(BTNode* parent, char* name, char* city);

/**
 * Searches for a Restaurant with a matching name and city in the BinaryTree
 * @param bt: BinaryTree to search for
 * @param name: name to search for
 * @param city: city to search for
 * @return: a pointer to the found Restaurant
 */
extern Restaurant* searchByNameAndCity(BinaryTree* bt, char* name, char* city);

/**
 * Converts the contents of the BinaryTree to a string
 * @param bt: BinaryTree to convert
 * @return: a pointer to a string
 */
extern char* toStringBinaryTree(BinaryTree* bt);

/**
 * Traverses a BinaryTree inorder and appends the string of the Node to the current one
 * @param node: the current BTNode
 * @param s: string to store the information
 */
extern void inOrderBinaryTree(BTNode* node, char* s);

/**
 * Removes the Restaurant from the BinaryTree by name
 * @param root: root of the BinaryTree
 * @param rest: Restaurant to remove
 * @return: a pointer to a BTNode
 */
extern BTNode* removeFromBTName(BTNode* root, Restaurant* rest);

/**
 * Removes the Restaurant from the BinaryTree by location
 * @param root: root of the BinaryTree
 * @param rest: Restaurant to remove
 * @return: a pointer to a BTNode
 */
extern BTNode* removeFromBTLocation(BTNode* root, Restaurant* rest);

/**
 * Searches for Restaurants matching with the given parameters
 * @param node: Node containing Restaurants with the searched location
 * @param found: ArrayList to contain the matching Restaurants
 * @param city: city to search for
 * @param type: food types to search for
 * @param timeArr: searched day and time
 * @param cost: search cost
 * @param comp: comparitor type - AND, OR, or single-search
 */
extern void searchCommand (BTNode* node, ArrayList* found, char* city, char** type, char** timeArr, char* cost, char* comp);

/**
 * Searches for Restaurants matching with the given parameters and the wild card for location
 * @param node: Node containing Restaurants with the searched location
 * @param found: ArrayList to contain the matching Restaurants
 * @param city: city to search for
 * @param type: food types to search for
 * @param timeArr: searched day and time
 * @param cost: search cost
 * @param comp: comparitor type - AND, OR, or single-search
 */
extern void searchWildCard(BTNode* node, ArrayList* found, char* city, char** type, char** timeArr, char* cost, char* comp);

/**
 * Frees the memory of the BinaryTree
 * @param node: current node to free
 */
extern void freeBT(BTNode* node);

#endif