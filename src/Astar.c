/*
 * Author: Rabeb JAOUADI
 * Purpose: Advanced C project: Implementation of an Astar algorithm.
 * Language:  C
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Astar.h"

/** function computinf the heuristics betweeen a given city and the destination
 * @return the heuristics.
 */
static int computeHeuristics(City* currentCity, City* destination)
{
    return (abs(currentCity->latitude - destination->latitude) +
            abs(currentCity->longitude - destination->longitude))/4;
}

/** Compute the exact cost from a city to its neighbor
 * @return the cost
 */
static int computeCost(City* city, Neighbor* neighbor)
{
    return (city->g + neighbor->distance);
}

/** Generates the solution path from the backpath generated by aStar.
 * @param backpath of cities and their parent cities generated from aStar.
 * @param the origin given to aStar.
 * @param the destination given to aSTar.
 * @return the solution path.
 */
static List* generatePath(List* backpath, City* origin, City* destination)
{
    List* path = newList(backpath->comp, backpath->pr);
    City* target = destination;
    int isFinished = 0;
    addList(path, destination);
    while(!isFinished)
    {
        int index = 0;
        Node* temp = backpath->head;
        while (temp)
        {
            CityFrom* city = (CityFrom*)temp->val;
            if (target->cityName == origin->cityName)
            {
                isFinished = 1;
                break;
            }
            if (city->childCity->cityName == target->cityName)
            {
                target = city->parentCity;
                addList(path, city->parentCity);
                free(temp->val);
                remFromListAt(backpath, index, temp);
                break;
            }
            temp = temp->next;
            index++;
        }
    }
    forEach(backpath, free);
    delList(backpath);
    return path;
}

/** aStar routing algorithm to find the best route possible from an origin to a destination.
 * @param List of the cities map with their neighbors to process.
 * @param string of the name of the origin.
 * param string of the name of the desination.
 * @return the optimal path from given origin towards the given destination.
 */
List* aStar(List* map, char* originName, char* destinationName, compFun comp)
{
    List* open = newList(comp, map->pr);
    List* closed = newList(comp, map->pr);
    List* backpath = newList(map->comp, map->pr);

    City* origin = searchCity(map, originName);
    City* destination = searchCity(map, destinationName);
    if (!origin || !destination)
        return 0;
    status st = addList(open, origin);
    if (st) return 0;
    origin->g = 0;
    origin->h = computeHeuristics(origin, destination);
    origin->f = origin->h;
    while (lengthList(open))
    {
        City* current = (City*) open->head->val;
        remFromList(open, current);
        addList(closed, current);
        if (current == destination)
        {
            delList(open);
            delList(closed);
            return generatePath(backpath, origin, destination);
        }
        Node* temp = current->neighbors->head;
        while(temp)
        {
            Neighbor* successor = (Neighbor*) temp->val;
            City* neighbor = successor->neighborPtr;
            int cost = computeCost (current, successor);

            if ( (isInList(closed, neighbor) ||
                  (isInList(open, neighbor)))
                     && cost > neighbor->g)
                temp = temp->next;
            else
            {
                if (isInList(open, neighbor))
                    remFromList(open, neighbor);
                neighbor->g = cost;
                neighbor->h = computeHeuristics(neighbor, destination);
                neighbor->f = neighbor->g + neighbor->h;
                if (!isInList(open, neighbor))
                    addList(open, neighbor);
                CityFrom* from = (CityFrom*)malloc(sizeof(CityFrom));
                from->childCity = neighbor;
                from->parentCity = current;
                addList(backpath, from);
                temp = temp->next;
            }
        }
    }
    return 0;
}
