/*
 * Author: Rabeb JAOUADI
 * Purpose: Advanced C project: Implementation of an Astar algorithm.
 * Language:  C
 */
#ifndef Utils_H_
#define Utils_H_

#include "List.h"

/**Struct definition of a city, it embeds the cities information and list
 * of its neighbors.
 */
typedef struct City {
    char cityName[15];
    int latitude;
    int longitude;
    int g;
    int h;
    int f;
    List* neighbors;
} City;

/** Struct definition of a neighbor pointing the neighbor City and its distance to the its related city.
 */
typedef struct Neighbor {
    City* neighborPtr;
    int distance;
} Neighbor;

/**
 * Search a List of cities for a given city.
 * @param List of cities to search.
 * @Param string to search in the list.
 * @return a pointer to the city if found
 * @return 0 if the city was not found
 */
City* searchCity(List* map, char* cityName);

#endif
