/*
 * Author: Rabeb JAOUADI
 * Purpose: Advanced C project: Implementation of an Astar algorithm.
 * Language:  C
 */
#ifndef aStar_H_
#define aStar_H_

#include "List.h"
#include "Utils.h"
#include <stdlib.h>

/** A structure definiton of a city kept by the aStar algorithm and the city it came from made for the purpose to create the path finding of the result.
 */
typedef struct CityFrom
{
    City* childCity;
    City* parentCity;
} CityFrom;

/** aStar routing algorithm to find the best route possible from an origin to a destination.
 * @param List of the cities map with their neighbors to process.
 * @param string of the name of the origin.
 * param string of the name of the desination.
 * @return the optimal path from given origin towards the given destination.
 */
List* aStar(List* map, char* originName, char* destinationName, compFun comp);

#endif
