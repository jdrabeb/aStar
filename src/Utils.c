/*
 * Author: Rabeb JAOUADI
 * Purpose: Advanced C project: Implementation of an Astar algorithm.
 * Language:  C
 */
#include <string.h>
#include "Utils.h"

/** Search a List of cities for a given city.
 * @param List of cities to search.
 * @Param string to search in the list.
 * @return a pointer to the city if found
 * @return 0 if the city was not found
 */
City* searchCity(List* map, char* cityName)
{
    Node* temp = map->head;
    while (temp)
    {
        City* currentCity = (City*) temp->val;
        if (strcmp(currentCity->cityName, cityName) == 0)
            return currentCity;
        else
            temp = temp->next;
    }
    return 0;
}

