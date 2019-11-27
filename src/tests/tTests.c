/*************************************************************
 *
 * $Id: tList.c 2102 2018-11-19 10:26:08Z phil $
 *
 *************************************************************
 */
/**
 * Sample test program for generic Lists : application to strings.
 *
 *************************************************************/

static char rcsId[] = "@(#) $Id: tList.c 2102 2018-11-19 10:26:08Z phil $";

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <string.h>
#include "List.h"
#include "Tests.h"


/*************************************************************
 * Function to compare two elements (strings) : based on strcmp
 * @param s1 the first string to compare
 * @param s2 the second string to compare
 * @return <0 if s1 is less than s2
 * @return 0 if s1 equals s2
 * @return >0 otherwise
 *************************************************************/
static int compString (void * s1, void * s2) {
  return strcmp((char*)s1, (char*)s2);
}

/*************************************************************
 * Function to display an element of the list
 * @param s the string to display
 *************************************************************
 */
static void prString(void * s) {
  printf("%s",(char*)s);
  printf("\n");
}

/*************************************************************
 * another display function, just to test "forEach"
 * @param s the string to display
 *************************************************************/
static void prString2 (void * s) {
  printf("%s\n",(char*)s);
}

/*************************************************************
 * test predicate for firstThat / allThat
 * @param s the element to test
 *************************************************************/
int startsWithM(void* s){
  return ((char*)s)[0] == 'm';
}

/*************************************************************
 * test program: creation of a list of strings then tests
 * for main list functionalities.
 *************************************************************/

int main() {
    int i; status st;
    char * tab[] = {"belle marquise", "vos beaux yeux", "me font",
		  "mourir", "d'amour" };
    char* s;

    /* list creation */
    List* l = newList(compString,prString);
    if (!l) return 1;
    testLengthEmptyList(l);

    /* populating list */
    for (i=0; i < sizeof(tab)/sizeof(char*); i++)
    addList(l,tab[i]);

    /* display list - should be sorted */
    displayList(l);
    putchar('\n');

    /*  test contain predicate */
    testIsInList(l);
    testisNotInList(l);
    testisInListFist(l);
    testIsInListLast(l);

    /* test element in list*/
    testFirstInList(l);
    testLastInList(l);
    testThirdInList(l);

    /* test add and remove element from list at position */
    testAddListAtFirst(l);
    testRemoveFromListAtFirst(l);

    testAddListAtLast(l);
    testRemoveFromListAtLast(l);

    testRemoveFromListAt(l);
    testAddListAt(l);


    /* test add and remove element from list */
    testAddListFirst(l);
    testRemoveFromListFirst(l);
    testAddListLast(l);
    testRemoveFromListLast(l);
    testRemoveFromList(l);
    testAddList(l);

    /* test length (beware: sizeof is long int!) */
    long tab_size = sizeof(tab)/sizeof(char*);
    testLengthList(l, tab_size);

    /* test forEach */
    puts("forEach:");
    forEach(l,prString2);

    /* test firstThat and allThat (memory not freed) */
    List* emptyList = newList(compString,prString);
    testFirstThat(l, startsWithM);
    testFirstThatNoFunction(l);
    testFirstThatEmptyList(emptyList, startsWithM);

    testAllThat(l, startsWithM, compString, prString);
    testAllThatNoFunction(l);
    testAllThatEmptyList(emptyList, startsWithM);
    /* final cleanup */
    delList(emptyList);
    delList(l);
    return 0;
}
/*************************************************************/
