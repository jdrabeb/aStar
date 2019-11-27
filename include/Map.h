/*
 * Author: Rabeb JAOUADI
 * Purpose: Advanced C project: Implementation of an Astar algorithm.
 * Language:  C
 */
#ifndef ParseMap_H_
#define ParseMap_H_

#include <stdio.h>
#include <limits.h>
#include "List.h"
#include "Utils.h"

#define INFINITE INT_MAX;

/** Generates List of cities and their neighboors from file.
 * @param file with cities and their neghboors.
 * @param com comparison function between elements.
 * @param pr display function for tlist elements.
 * @return List of cities filled from the file.
*/
List* generateMap(FILE* file, compFun comp, prFun pr);

#endif
