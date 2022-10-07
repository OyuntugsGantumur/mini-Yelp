#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

int main() {

    BinaryTree* btName = createBinaryTree();
    BinaryTree* btLocation = createBinaryTree();
    readFile(btName, "Name");
    readFile(btLocation, "Location");

    char command[3];
    char name_search[30];
    char city_search[30];
    char type_search[50];
    char cost_search[5];
    char time_search[30];
    char hour_search[150];
    char rank_search[5];
    char review_search[5];

    printf("Please enter your command!\n");
    printf("- a to add a new restaurant\n");
    printf("- p to print all restaurant information\n");
    printf("- s to search restaurants\n");
    printf("- e to explore with name and location\n");
    printf("- r to remove a restaurant\n");
    printf("- m to modify/update restaurant information\n");
    printf("- w to write to a file\n");
    printf("- x to exit\n");
    
    fgets(command, 5, stdin);
    command[strcspn(command, "\n")] = 0;

    while(strcmp(command, "x") != 0) {

        if(strcmp(command, "p") == 0) {

            printf("%s", toStringBinaryTree(btName));
        
        } else if (strcmp(command, "w") == 0) {

            writeFile(btName);
            printf("Restaurants' information is written in newrestaurants.txt file!\n");

        } else if(strcmp(command, "e") == 0) {
 
            printf("Name input: ");
            fgets(name_search, 30, stdin);
            printf("City input: ");
            fgets(city_search, 30, stdin);

            name_search[strcspn(name_search, "\n")] = 0;
            city_search[strcspn(city_search, "\n")] = 0;

            Restaurant* found = searchByNameAndCity(btLocation, name_search, city_search);
            if(found == NULL) printf("No restaurant is found!\n"); 
            else printf("%s\n", printRestaurant( *found ));

        } else if(strcmp(command, "a") == 0) {
            
            printf("Name to add: ");
            fgets(name_search, 30, stdin);
            printf("City input: ");
            fgets(city_search, 30, stdin);
            printf("Type: ");
            fgets(type_search, 30, stdin);
            printf("Hours: ");
            fgets(hour_search, 150, stdin);
            printf("Cost: ");
            fgets(cost_search, 5, stdin);
            printf("Rank: ");
            fgets(rank_search, 5, stdin);
            printf("Reviews: ");
            fgets(review_search, 5, stdin);

            name_search[strcspn(name_search, "\n")] = 0;
            city_search[strcspn(city_search, "\n")] = 0;
            type_search[strcspn(type_search, "\n")] = 0;
            hour_search[strcspn(hour_search, "\n")] = 0;
            cost_search[strcspn(cost_search, "\n")] = 0;
            rank_search[strcspn(rank_search, "\n")] = 0;
            review_search[strcspn(review_search, "\n")] = 0;

            char*** dayHours = (char***) malloc (100 * sizeof(char**));
            divideDayTime(hour_search, dayHours, ",");
            char** foodType = (char**) malloc (10 * sizeof(char*)); //is type defined?????????
            divideFoodType(type_search, foodType, ", ");

            Restaurant* restToAdd = initRestaurant(name_search, city_search, foodType, dayHours, cost_search, atof(rank_search), atoi(review_search));

            insertByName(btName, restToAdd);
            insertByLocation(btLocation, restToAdd);

        } else if(strcmp(command, "r") == 0) {

            // removes a restaurant from all trees
            printf("Name to delete: ");
            fgets(name_search, 30, stdin);
            printf("City to delete: ");
            fgets(city_search, 30, stdin);

            name_search[strcspn(name_search, "\n")] = 0;
            city_search[strcspn(city_search, "\n")] = 0;

            Restaurant* found = searchByNameAndCity(btLocation, name_search, city_search);
            if(found == NULL) {
                printf("No restaurant is found!\n"); 
            } else {
                removeFromBTLocation(btLocation->root, found);
                removeFromBTName(btName->root, found);
            }

        } else if(strcmp(command, "m") == 0) {

            //modifies a restaurant found by name and location
            printf("Name to modify: ");
            fgets(name_search, 30, stdin);
            printf("City input: ");
            fgets(city_search, 30, stdin);
            printf("Type: ");
            fgets(type_search, 30, stdin);
            printf("Hours: ");
            fgets(hour_search, 150, stdin);
            printf("Cost: ");
            fgets(cost_search, 5, stdin);
            printf("Rank: ");
            fgets(rank_search, 5, stdin);
            printf("Reviews: ");
            fgets(review_search, 5, stdin);

            name_search[strcspn(name_search, "\n")] = 0;
            city_search[strcspn(city_search, "\n")] = 0;
            type_search[strcspn(type_search, "\n")] = 0;
            hour_search[strcspn(hour_search, "\n")] = 0;
            cost_search[strcspn(cost_search, "\n")] = 0;
            rank_search[strcspn(rank_search, "\n")] = 0;
            review_search[strcspn(review_search, "\n")] = 0;

            char*** dayHours = (char***) malloc (100 * sizeof(char**));
            divideDayTime(hour_search, dayHours, ",");
            char** foodType = (char**) malloc (10 * sizeof(char*));
            divideFoodType(type_search, foodType, ", ");

            Restaurant* restToModify = searchByNameAndCity(btLocation, name_search, city_search);

            if(restToModify == NULL) {
                printf("No restaurant is found!\n"); 
            } else {
                restToModify->categories = foodType;
                restToModify->hours = dayHours;
                restToModify->cost = cost_search;
                restToModify->rank = atof(rank_search);
                restToModify->reviewers = atoi(review_search);

                printf("Restaurant is modified!\n");
            }

            // printf("%s\n", printRestaurant(*restToModify));
        
        } else if (strcmp(command, "s") == 0) {

            printf("City input: ");
            fgets(city_search, 30, stdin);
            printf("Type: ");
            fgets(type_search, 30, stdin);
            printf("Cost: ");
            fgets(cost_search, 5, stdin);
            printf("Hours: ");
            fgets(hour_search, 150, stdin);
            
            city_search[strcspn(city_search, "\n")] = 0;
            type_search[strcspn(type_search, "\n")] = 0;
            hour_search[strcspn(hour_search, "\n")] = 0;
            cost_search[strcspn(cost_search, "\n")] = 0;

            ArrayList* found = createArrayList();
            char** foodType = (char**) malloc (10 * sizeof(char*));
            char* comparitor = (char*) malloc (3 * sizeof(char));

            //Dividing the parameter time into its day and hour componenets
            char** timeArr = (char**) malloc (20 * sizeof (char*));
            char** temp = timeArr;
            char* str;
            char* end = strdup(hour_search);
            while((str = strsep(&end, " ")) != NULL) {
                *temp = (char*) malloc (10 * sizeof(char));
                *temp = str;
                temp++;
            }

            if(strstr(type_search, "OR")) {
                divideFoodType(type_search, foodType, "OR ");
                comparitor = "OR";
            } else if (strstr(type_search, ",")) {
                divideFoodType(type_search, foodType, ", ");
                comparitor = "AND";
            } else {
                divideFoodType(type_search, foodType, " ");
                comparitor = "*";
            }

            if(strcmp(city_search, "*") == 0) {
                searchWildCard(btLocation->root, found, city_search, foodType, timeArr, cost_search, comparitor);
            } else {
                BTNode* curr = searchRecursive(btLocation->root, "", city_search);
                searchCommand(curr, found, city_search, foodType, timeArr, cost_search, comparitor);
            }

            printf("\n%s", printArray(found));

        } else {
            printf("Invalid command!\n");
        }

        printf("Please enter your command!\n");
        fgets(command, 5, stdin);
        command[strcspn(command, "\n")] = 0;
    }

    printf("Bye!");

    freeBT(btName->root);
    freeBT(btLocation->root);
    free(btName);
    free(btLocation);

    return 0;
}
