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
    char origin[15];
    char destination[15];
    char fileName[30];
    if (argc <= 2)
    {
        char choice;
        if (argc == 1)
        {
            printf("Enter the origin:\n");
            scanf("%s", origin);
        }
        else
        {
            sscanf(args[1], "%s", origin);
        }
        printf("Enter the destination:\n");
        scanf("%s", destination);
        printf("Enter file name (Y) or load default file (N): (Y/N)\n");
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y')
        {
            printf("Enter new filename:\n");
            scanf("%s", fileName);
        }
        else if (choice == 'N' || choice == 'n')
            strcpy(fileName, "FRANCE.MAP");
        else
        {
            printf("Unknown choice. Exiting..\n");
            return 0;
        }
    }
    else
    {
        sscanf(args[1], "%s", origin);
        sscanf(args[2], "%s", destination);
        if (argc == 4)
            sscanf(args[3], "%s", fileName);
        else
            strcpy(fileName, "FRANCE.MAP");
    }
    FILE *franceMap = fopen(fileName, "r");
    if (franceMap == 0)
    {
        printf("Error opening file.");
        return 0;
    }
    List* map = generateMap(franceMap, compN, display);
    pclose(franceMap);

    List* path = aStar(map, origin, destination, minF);
    printf("The shorted path is: \n\n");
    displayList(path);

    forEach(map, delCity);
    delList(map);
    delList(path);
    return 0;
}
