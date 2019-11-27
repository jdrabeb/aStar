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
void testLengthList(List* l, long tab_size)
{
    assert(lengthList(l) == tab_size);
}

void testLengthEmptyList(List* l)
{
    assert(lengthList(l) == 0);
}

/*
 * Test nthInList
*/

void testFirstInList (List* l)
{
    char* s;
    assert(!nthInList(l, 1, &s));
    assert(strcmp(s,"belle marquise") == 0);
}

void testLastInList (List* l)
{
    char* s;
    assert(!nthInList(l, l->nelts, &s));
    assert(strcmp(s, "vos beaux yeux") == 0);
}

void testThirdInList (List* l)
{
    char* s;
    assert(!nthInList(l, 3, &s));
    assert(strcmp(s, "me font") == 0);
}

/*
 * Test isInList
*/
void testisInListFist (List* l)
{
    assert(isInList(l, "belle marquise") == (void*) 1);
}

void testisNotInList (List* l)
{
    assert(isInList(l, "vivre") == 0);
}

void testIsInList (List* l)
{
    assert(isInList(l, "mourir") != 0);
}

void testIsInListLast (List* l)
{
    assert(isInList(l, "vos beaux yeux") != 0);
}

/*
 * Test Add to list at position
*/
void testAddListAtFirst(List* l)
{
    char* s = "added first";
    int neltsBeforeAdding = l->nelts;
    assert(!addListAt(l, 1, s));
    assert(isInList(l, "added first") == (void*) 1);
    assert(l->nelts == neltsBeforeAdding + 1);
}

void testAddListAt(List* l)
{
    char* s = "mourir";
    int neltsBeforeAdding = l->nelts;
    assert(!addListAt(l, 4, s));
    assert(isInList(l, "mourir") != 0);
    assert(l->nelts == neltsBeforeAdding + 1);
}

void testAddListAtLast(List* l)
{
    char* s = "add last";
    int neltsBeforeAdding = l->nelts;
    assert(!addListAt(l, neltsBeforeAdding + 1, s));
    assert(isInList(l, "add last") != 0);
    assert(l->nelts == neltsBeforeAdding + 1);
}

/*
 * Test remove from list at poisition
*/
void testRemoveFromListAtFirst(List* l)
{
    char* s;
    int neltsBeforeRemove = l->nelts;
    assert(!remFromListAt(l, 1, &s));
    assert(strcmp(s, "added first") == 0);
    assert(l->nelts == neltsBeforeRemove - 1);
}

void testRemoveFromListAt(List* l)
{
    char* s;
    int neltsBeforeRemove = l->nelts;
    assert(!remFromListAt(l, 4, &s));
    assert(strcmp(s, "mourir") == 0);
    assert(l->nelts == neltsBeforeRemove - 1);
}

void testRemoveFromListAtLast(List* l)
{
    char* s;
    int neltsBeforeRemove = l->nelts;
    assert(!remFromListAt(l, l->nelts, &s));
    assert(strcmp(s, "add last") == 0);
    assert(l->nelts == neltsBeforeRemove - 1);
}

/*
 * Test Add to list
*/
void testAddListFirst(List* l)
{
    char* s = "added first";
    int neltsBeforeAdding = l->nelts;
    assert(!addList(l, s));
    assert(isInList(l, "added first") == (void*) 1);
    assert(l->nelts == neltsBeforeAdding + 1);
}

void testAddList(List* l)
{
    char* s = "mourir";
    int neltsBeforeAdding = l->nelts;
    assert(!addList(l, s));
    assert(isInList(l, "mourir") != 0);
    assert(l->nelts == neltsBeforeAdding + 1);
}

void testAddListLast(List* l)
{
    char* s = "zombie";
    int neltsBeforeAdding = l->nelts;
    assert(!addList(l, s));
    assert(isInList(l, "zombie") != 0);
    assert(l->nelts == neltsBeforeAdding + 1);
}

/*
 * Test remove from list
*/
void testRemoveFromListFirst(List* l)
{
    char* s = "added first";
    int neltsBeforeRemove = l->nelts;
    assert(!remFromList(l, s));
    assert(l->nelts == neltsBeforeRemove - 1);
}

void testRemoveFromList(List* l)
{
    char* s;
    int neltsBeforeRemove = l->nelts;
    assert(!remFromListAt(l, 4, &s));
    assert(l->nelts == neltsBeforeRemove - 1);
}

void testRemoveFromListLast(List* l)
{
    char* s = "zombie";
    int neltsBeforeRemove = l->nelts;
    assert(!remFromList(l, s));
    assert(l->nelts == neltsBeforeRemove - 1);
}

/*
 * Test first that
*/
void testFirstThat(List* l, int(*f)(void*))
{
    char* s = firstThat(l, f);
    char* expected = "me font";
    assert(strcmp(s,expected) == 0);
}

void testFirstThatNoFunction(List* l)
{
    char* s = firstThat(l, 0);
    assert(s == 0);

}

void testFirstThatEmptyList(List* l, int(*f)(void*))
{
    char* s = firstThat(l, f);
    assert(s == 0);
}

/*
 * Test all that
*/
void testAllThat(List* l, int(*f)(void*), compFun comp, prFun pr)
{
    List* matchList = allThat(l, f);
    List* expectedList = newList(comp, pr);
    addList(expectedList, "me font");
    addList(expectedList, "mourir");
    Node* tempMatch = matchList->head;
    Node* tempExpected = expectedList->head;
    assert(matchList->nelts == expectedList->nelts);
    while(tempMatch && tempExpected)
    {
        assert(strcmp(tempMatch->val, tempExpected->val) == 0);
        tempMatch = tempMatch->next;
        tempExpected = tempExpected->next;
    }
    delList(matchList);
    delList(expectedList);
}

void testAllThatNoFunction(List* l)
{
    List* matchList = allThat(l, 0);
    assert(matchList == 0);
}

void testAllThatEmptyList(List* l, int(*f)(void*))
{
    List* matchList = allThat(l, f);
    assert(matchList->nelts == 0);
    free(matchList);
}

/*************************************************************/
