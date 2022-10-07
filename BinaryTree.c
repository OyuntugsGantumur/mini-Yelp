#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryTree.h"


/**
 * Create an empty BinaryTree with 0 elements
 * @return a pointer to a BinaryTree
 */
BinaryTree* createBinaryTree() {
    BinaryTree* tree = (BinaryTree*) malloc(sizeof(BinaryTree));
    tree -> root = NULL;
    tree -> size = 0;
    return tree;
}

/**
 * Recursively searches for the right place for the Restaurant by name and inserts the Restaurant at that position
 * If a Restaurant with the same name already exists, adds the Restaurant to the arraylist
 * @param parent: parent of the node to be inserted in
 * @param rest: Restaurant to insert
 */
void insertByNameRecursive(BTNode* parent, Restaurant* rest) {
    if(strcmp(parent->name, rest->name) < 0) {
        
        if(parent->left == NULL) {
            parent->left = (BTNode*) malloc (sizeof (BTNode));
            parent->left->arr = createArrayList();
            addInArray(parent->left->arr, rest);
            parent->left->name = rest->name;
        } else {
            insertByNameRecursive(parent->left, rest);
        }

    } else if(strcmp(parent->name, rest->name) > 0){

        if(parent->right == NULL) {
            parent->right = (BTNode*) malloc (sizeof (BTNode));
            parent->right->arr = createArrayList();
            addInArray(parent->right->arr, rest);
            parent->right->name = rest->name;
        } else {
            insertByNameRecursive(parent->right, rest);
        }

    } else {
        addInArray(parent->arr, rest);
    }
}

/**
 * Inserts the Restaurant into the BinaryTree by its name and calls the recursive insert method
 * @param bt: BinaryTree to insert in
 * @param rest: Restaurant to be inserted
 */
void insertByName(BinaryTree* bt, Restaurant* rest) {

    if(bt -> root == NULL) {
        bt->root = (BTNode*) malloc (sizeof (BTNode));
        bt->root->arr = createArrayList();
        addInArray(bt->root->arr, rest);
        bt->root->name = rest->name;
        bt->size++;
    } else {
        insertByNameRecursive(bt->root, rest);
        bt->size++;
    }
}

/**
 * Recursively searches for the right place for the Restaurant by location and inserts the Restaurant at that position
 * If a Restaurant with the same name already exists, adds the Restaurant to the arraylist
 * @param parent: parent of the node to be inserted in
 * @param rest: Restaurant to insert
 */
void insertByLocationRecursive(BTNode* parent, Restaurant* rest) {
    if(strcmp(parent->name, rest->city) < 0) {
        
        if(parent->left == NULL) {
            parent->left = (BTNode*) malloc (sizeof (BTNode));
            parent->left->arr = createArrayList();
            addInArray(parent->left->arr, rest);
            parent->left->name = rest->city;
        } else {
            insertByLocationRecursive(parent->left, rest);
        }

    } else if(strcmp(parent->name, rest->city) > 0){

        if(parent->right == NULL) {
            parent->right = (BTNode*) malloc (sizeof (BTNode));
            parent->right->arr = createArrayList();
            addInArray(parent->right->arr, rest);
            parent->right->name = rest->city;
        } else {
            insertByLocationRecursive(parent->right, rest);
        }

    } else {
        addInArray(parent->arr, rest);
    }
}

/**
 * Inserts the Restaurant into the BinaryTree by its location and calls the recursive insert method
 * @param bt: BinaryTree to insert in
 * @param rest: Restaurant to be inserted
 */
void insertByLocation(BinaryTree* bt, Restaurant* rest) {

    if(bt -> root == NULL) {
        bt->root = (BTNode*) malloc (sizeof (BTNode));
        bt->root->arr = createArrayList();
        addInArray(bt->root->arr, rest);
        bt->root->name = rest->city;
        bt->size++;
    } else {
        insertByLocationRecursive(bt->root, rest);
        bt->size++;
    }
}

/**
 * Recursively searches for a BTNode with the matching city. If there's none, returns null.
 * @param parent: parent of the node with the same city name
 * @param name: name to search for
 * @param city: city to search for
 * @return: BTNode with the same city name
 */
BTNode* searchRecursive(BTNode* parent, char* name, char* city) {
    if(parent != NULL) {
        if(strcmp(parent->name, city) == 0) {
            return parent;
        } else if(strcmp(parent->name, city) < 0) {
            return searchRecursive(parent->left, name, city);
        } else if (strcmp(parent->name, city) > 0) {
            return searchRecursive(parent->right, name, city);
        }
    }
    
    return (BTNode*)NULL;
}

/**
 * Searches for a Restaurant with the matching name and city in the BinaryTree and calls the recursive search method
 * If there's no matching Restaurant, return null.
 * @param bt: BinaryTree to search
 * @param name: name of the Restaurant
 * @param city: city of the Restaurant
 * @return: a pointer to the found Restaurant
 */
Restaurant* searchByNameAndCity(BinaryTree* bt, char* name, char* city) {
    BTNode* temp = searchRecursive(bt->root, name, city);

    if( temp != NULL ) {
        return searchRestaurant(temp->arr, name, city);
    } 
    
    return (Restaurant*) NULL;
}

/**
 * Converts the contents of the BinaryTree into a string by calling inorder traversal method
 * @param bt: BinaryTree to convert
 * @return: a pointer to a string
 */
char* toStringBinaryTree(BinaryTree* bt) {
    if(bt->root != NULL) {
        char* buffer = (char*) malloc ((bt->size * 400) * sizeof(char));
        inOrderBinaryTree(bt->root, buffer);
        return buffer;
    }
    
    return (char*)NULL;
}

/**
 * Traverses the BinaryTree in order and appends the information of each node to a string
 * @param node: current BTNode
 * @param s: string containing the information
 */
void inOrderBinaryTree(BTNode* node, char* s) {
    if(node == NULL) return;

    inOrderBinaryTree(node -> right, s);
    sprintf(&s[strlen(s)], "%s", printArray(node->arr));
    inOrderBinaryTree(node -> left, s);  
}

/**
 * Removes the Restaurant from the BinaryTree of names by checking all possible cases: node with two children, node with one child and node with no child
 * @param root: root of the BinaryTree
 * @param rest: Restaurant to remove
 * @return BTNode containing the Restaurant
 */
BTNode* removeFromBTName(BTNode* root, Restaurant* rest) {
    if(root == NULL) return root;

    if(strcmp(root->name, rest->name) > 0) {
        root->right = removeFromBTName(root->right, rest);
        return root;
    } else if(strcmp(root->name, rest->name) < 0) {
        root->left = removeFromBTName(root->left, rest);
        return root;
    } else {

        if(root->arr->num_elements > 1){
            removeFromArray(root->arr, rest);
            return root;
        }

        //if the root has one or no child. 
        if(root->left == NULL) {
                
                BTNode* temp = root->right;
                return temp;
            
        } else if(root->right == NULL) {
                
                BTNode* temp = root->left;
                return temp;
        }

        //if the root has two children
        BTNode* curr = root->right;
        while(curr->left != NULL) {
            curr = curr->left;
        }

        root->arr = curr->arr;
        
        if(curr->arr->num_elements == 1) {
            root->right = removeFromBTName(root->right, curr->arr->resptr[0]);
        } else {
            for(int i = 0; i < curr->arr->num_elements; i++) {
                root->right = removeFromBTName(root->right, curr->arr->resptr[i]);
            }
        }
        return root;
    }

    printf("Restaurant NOT FOUND!!!\n");
    return (BTNode*) NULL;
}

/**
 * Removes the Restaurant from the BinaryTree of locations by checking all possible cases: node with two children, node with one child and node with no child
 * @param root: root of the BinaryTree
 * @param rest: Restaurant to remove
 * @return BTNode containing the Restaurant
 */
BTNode* removeFromBTLocation(BTNode* root, Restaurant* rest) {
    if(root == NULL) return root;

    if(strcmp(root->name, rest->city) > 0) {
        root->right = removeFromBTLocation(root->right, rest);
        return root;
    } else if(strcmp(root->name, rest->city) < 0) {
        root->left = removeFromBTLocation(root->left, rest);
        return root;
    } else {

        if(root->arr->num_elements > 1){
            removeFromArray(root->arr, rest);
            return root;
        }

        //if the root has one or no child. 
        if(root->left == NULL) {
                
                BTNode* temp = root->right;
                return temp;
            
        } else if(root->right == NULL) {
                
                BTNode* temp = root->left;
                return temp;
        }

        //if the root has two children
        BTNode* curr = root->right;
        while(curr->left != NULL) {
            curr = curr->left;
        }

        root->arr = curr->arr;
        
        if(curr->arr->num_elements == 1) {
            root->right = removeFromBTLocation(root->right, curr->arr->resptr[0]);
        } else {
            for(int i = 0; i < curr->arr->num_elements; i++) {
                root->right = removeFromBTLocation(root->right, curr->arr->resptr[i]);
            }
        }
        return root;
    }

    printf("Restaurant NOT FOUND!!!\n");
    return (BTNode*) NULL;
}

/**
 * Checks if an array of strings contains the specified string
 * @param src: an array of string
 * @param search: a string to search for
 * @return: true if it contains, otherwise false
 */
bool containsType(char** src, char* search) {
    char** temp = src;

    while(temp[0] != NULL) {
        if(strcmp(temp[0], search) == 0) return true;
        temp++;
    }

    return false;
}

/**
 * Checks if the an array of strings contains all the strings in another array
 * @param restType: an array of food type Restaurant serves to search in
 * @param search: an array of string to search for
 * @return: true if the restType contains all strings in search, otherwise false
 */
bool ANDcomparitor(char** restType, char** search) {
    char** temp = search;

    while(temp[0] != NULL) {
        if(!containsType(restType, *temp)) return false;
        temp++;
    }

    return true;
}

/**
 * Checks if the restaurant type contains at least one of the strings in searched types
 * @param restType: food types Restaurant serves
 * @param input: food types searched by the user
 * @return true if the restType contains at least one of the inputs
 */
bool ORcomparitor (char** restType, char** input) {
    char** comp1 = restType;
    char** comp2 = input;

    while(comp2[0] != NULL) {
        comp1 = restType;

        while(comp1[0] != NULL) {
            if(strcmp(comp2[0], comp1[0]) == 0) {
                return true;
            }

            comp1++;
        }

        comp2++;
    }
    return false;
}

/**
 * Searches for Restaurants matching with the input types including AND and OR for food types and adds them to an ArrayList
 * @param node: node contains Restaurants with the matching city
 * @param found: ArrayList to add the matching Restaurants
 * @param city: city to search for
 * @param type: food types to search for
 * @param timeArra: desired day and time of the week
 * @param cost: desired cost
 * @param comp: comparitor type for food types - AND, OR, or single-search
 */
void searchCommand (BTNode* node, ArrayList* found, char* city, char** type, char** timeArr, char* cost, char* comp) {

    for(int i = 0; i < node->arr->num_elements; i++) {
        Restaurant* curr = node->arr->resptr[i];
        
        if(strlen(curr->cost) <=  strlen(cost) ) {
            if((strcmp(comp, "*") == 0 && containsType(curr->categories, *type) )|| (strcmp(comp, "OR") == 0 && ORcomparitor(curr->categories, type)) || (strcmp(comp, "AND") == 0 && ANDcomparitor(curr->categories, type))) { 
                for(int j = 0; j < 7 && curr->hours[j] != NULL; j++) {
                    char** worktime = curr->hours[j];
                    
                    if( strcmp(worktime[0], timeArr[0])==0 && (strcmp(worktime[1], timeArr[1])<= 0 || strlen(worktime[1]) < strlen(timeArr[1])) && strcmp(worktime[2], timeArr[1])>0 ) {

                        addInArray(found, curr);
                    }
                }   
            }
        }
    }

    return;
}

/**
 * Searches for matching Restaurants using the wild card for the city by implementing postorder traversal and searching for matching Restaurants in each BTNode
 * @param node: current BTNode
 * @param found: ArrayList to add the matching Restaurants in
 * @param city: city to search for
 * @param type: food types to search for
 * @param timeArr: desired day and time of the day
 * @param cost: desired cost
 * @param comp: comparitor type for food types
 */
void searchWildCard(BTNode* node, ArrayList* found, char* city, char** type, char** timeArr, char* cost, char* comp) {
    if(node == NULL) return;

    searchWildCard(node->left, found, city, type, timeArr, cost, comp);
    searchWildCard(node->right, found, city, type, timeArr, cost, comp);

    searchCommand(node, found, city, type, timeArr, cost, comp);
    return;
}

/**
 * Frees the memory of the BinaryTree and BTNode by implementing postorder traversal
 * @param node: current node of the BinaryTree
 */
void freeBT(BTNode* node) {
    if(node == NULL) return;

    freeBT(node->left);
    freeBT(node->right);

    freeAL(node->arr);
    free(node);
    return;
}