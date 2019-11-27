/*
 * Author: Rabeb JAOUADI
 * Purpose: Advanced C project: Implementation of an Astar algorithm.
 * Language:  C
 */
#include <string.h>
#include "Map.h"

/** Generates List of cities and their neighbors from file.
 * @param file with cities and their neghboors.
 * @param com comparison function between elements.
 * @param pr display function for tlist elements.
 * @return List of cities filled from the file.
*/
List* generateMap(FILE* file, compFun comp, prFun pr)
{
    char cityName[15];
    int x;
    int y;
    List* map = newList(comp, pr);
    int ret = 0;
    City* currentCity;
    while (1)
    {
        ret = fscanf(file, "%s %d %d", cityName, &x, &y);
        if (ret == EOF)
            break;
        if (ret == 2)
        {
            Neighbor *neighbor = (Neighbor*)malloc(sizeof(Neighbor));
            City* currentNeighbor = searchCity(map, cityName);
            if (currentNeighbor)
            {
                neighbor->neighborPtr = currentNeighbor;
                neighbor->distance = x;
                addList(currentCity->neighbors, neighbor);
            }
            else
            {
                currentNeighbor = (City*)malloc(sizeof(City));
                List* neighbors = newList(comp, pr);
                strcpy(currentNeighbor->cityName, cityName);
                currentNeighbor->g = INFINITE;
                currentNeighbor->h = 0;
                currentNeighbor->f = 0;
                currentNeighbor->neighbors = neighbors;
                addList(map, currentNeighbor);
                neighbor->neighborPtr = currentNeighbor;
                neighbor->distance = x;
                addList(currentCity->neighbors, neighbor);
            }
        }
        else if (ret == 3)
        {
            currentCity = searchCity(map, cityName);
            if (currentCity)
            {
                currentCity->latitude = x;
                currentCity->longitude = y;
            }
            else
            {
                currentCity = (City*)malloc(sizeof(City));
                List* neighbors = newList(comp, pr);
                strcpy(currentCity->cityName, cityName);
                currentCity->latitude = x;
                currentCity->longitude = y;
                currentCity->g = INFINITE;
                currentCity->h = 0;
                currentCity->f = 0;
                currentCity->neighbors = neighbors;
                addList(map, currentCity);
            }
        }
    }
    return map;
}

