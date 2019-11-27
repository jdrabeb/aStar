/*
 * Author: Rabeb JAOUADI
 * Purpose: Advanced C project: Implementation of an Astar algorithm.
 * Language:  C
 */
#include <string.h>
#include "Map.h"
#include "Astar.h"

/** Function to compare two f values of two different cities:
 * @param s1 the first city
 * @param s2 the second city
 * @return <0 if s1->f is less than s2->f
 * @return 0 if s1->f equal s2->f
 * @return >0 otherwise
 */
static int minF(void* s1, void* s2)
{
    City* city1 = (City*) s1;
    City* city2 = (City*) s2;
    if (city1->f < city2->f)
        return -1;
    else if (city1->f == city2->f)
        return 0;
    else
        return 1;
}

/**Dummy compare function to generate map with the same order as the file.
 * @param s1 first city
 * @param s2 second city
 * @return comparaison value
 */
static int compN(void* s1, void* s2)
{
    return s1 == s2;
}

/**Function to display a city
 * @param s the city to display
 */
static void display(void *s)
{
    City *city = (City*) s;
    printf("%s\n", city->cityName);
}

/**Function to free a City structure
 * @param s the city to free
 */
static void delCity(void *s)
{
    City* city = (City*) s;
    forEach(city->neighbors, free);
    delList(city->neighbors);
    free(city);
}

int main(int argc, char* args[])
{
    if (argc == 1)
    {
        printf("Must include filename to create the list");
        return 0;
    }
    char* fileName = args[1];
    FILE *franceMap = fopen(fileName, "r");
    if (franceMap == 0)
    {
        printf("Error opening file.");
        return 0;
    }
    List* map = generateMap(franceMap, compN, display);
    pclose(franceMap);

    List* path = aStar(map, "Rennes", "Lyon", minF);
    printf("The shorted path is: \n\n");
    displayList(path);

    forEach(map, delCity);
    delList(map);
    delList(path);
    return 0;
}
