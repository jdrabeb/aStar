#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <string.h>
#include "List.h"

/*************************************************************
 * test program: creation of a list of strings then tests
 * for main list functionalities.
 *************************************************************/

/*
 * Test length of a list
*/
void testLengthList(List* l, long tab_size);
void testLengthEmptyList(List* l);
/*
 * Test nthInList
*/
void testFirstInList (List* l);
void testLastInList (List* l);
void testThirdInList (List* l);
/*
 * Test isInList
*/
void testisInListFist (List* l);
void testisNotInList (List* l);
void testIsInList (List* l);
void testIsInListLast (List* l);
/*
 * Test Add to list at position
*/
void testAddListAtFirst(List* l);
void testAddListAt(List* l);
void testAddListAtLast(List* l);
/*
 * Test remove from list at position
*/
void testRemoveFromListAtFirst(List* l);
void testRemoveFromListAt(List* l);
void testRemoveFromListAtLast(List* l);
/*
 * Test Add to list
*/
void testAddListFirst(List* l);
void testAddList(List* l);
void testAddListLast(List* l);
/*
 * Test remove from list
*/
void testRemoveFromListFirst(List* l);
void testRemoveFromList(List* l);
void testRemoveFromListLast(List* l);
/*
 * Test first that
*/
void testFirstThat(List* l, int(*f)(void*));
void testFirstThatNoFunction(List* l);
void testFirstThatEmptyList(List* l, int(*f)(void*));
/*
 * Test all that
*/
void testAllThat(List* l, int(*f)(void*), compFun comp, prFun pr);
void testAllThatNoFunction(List* l);
void testAllThatEmptyList(List* l, int(*f)(void*));

/*************************************************************/
