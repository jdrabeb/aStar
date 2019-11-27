/**
 *
 * Creation of a generic (simply linked) List structure.
 *
 * To create a list, one must provide two functions (one function to
 * compare / order elements, one function to display them). Unlike arrays,
 * indices begins with 1.
 *
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "List.h"

/** Empty List creation by dynamic memory allocation (O(1)).
 * @param comp comparison function between elements (ala strcmp())
 * @param pr display function for list elements
 * @return a new (empty) list if memory allocation OK
 * @return 0 otherwise
 */
List*	newList	(compFun comp, prFun pr)
{
    List* l = (List*)malloc(sizeof(List));
    if (!l)
        return 0;
    l->nelts = 0;
    l->head = 0;
    l->comp = comp;
    l->pr = pr;
    return l;
}

/** destroy the list by deallocating used memory (O(N)).
 * @param l the list to destroy */
void 	delList	(List* l)
{
    Node* temp = l->head;
    while (temp)
    {
        l->head = temp->next;
        free(temp);
        temp = l->head;
    }
    free(l);
}

/** get the Nth element of the list (O(N)).
 * @param l the list
 * @param n the index of the element in list
 * @param res (out) the searched element
 * @return OK if element found
 * @return ERRINDEX if index out of list bounds
 */
status 	nthInList	(List* l, int n, void* res)
{
    if (n > l->nelts || n <= 0)
        return ERRINDEX;
    Node* temp = l->head;
    for (int i = 1; i<n; i++)
    {
        temp = temp->next;
    }
     *(void**)res = temp->val;
    return OK;
}

/** Insert element at a given position in the list (O(N)).
 * @param l the list to store the element in
 * @param n the position of the insertion point
 * @param e the element to insert
 * @return ERRINDEX if position is out of list bounds
 * @return ERRALLOC if memory allocation failed
 * @return OK otherwise
 */
status 	addListAt	(List* l, int n, void* e)
{
    if (n > l->nelts + 1)
        return ERRINDEX;
    Node* temp = l->head;
    Node* newVal = (Node*)malloc(sizeof(Node));
    if (!newVal)
        return ERRALLOC;
    if (n == 1)
    {
        newVal->next = temp;
        newVal->val = e;
        l->head = newVal;
        l->nelts++;
        return OK;
    }
    for (int i=1; i<n-1;i++)
        temp = temp->next;
    newVal->next = temp->next;
    newVal->val = e;
    temp->next = newVal;
    l->nelts++;
    return OK;
}

/** remove the element located at a given position in list (O(N)).
 * @param l the list to remove the element from
 * @param n the position of the element to remove
 * @param res (out) the removed element
 * @return ERRINDEX if position is out of list bounds
 * @return OK otherwise
 */
status 	remFromListAt	(List* l, int n, void* res)
{
    if (n > l->nelts)
        return ERRINDEX;
    Node* temp = l->head;
    if (n == 1)
    {
        *(void**)res = temp->val;
        l->head = temp->next;
        free(temp);
        temp = 0;
        l->nelts--;
        return OK;
    }
    for (int i=1; i<n-1;i++)
        temp = temp->next;
    Node* toRemove = temp->next;
    *(void**)res = toRemove->val;
    if (!temp->next->next)
        temp->next = 0;
    else
        temp->next = temp->next->next;
    free(toRemove);
    toRemove = 0;
    l->nelts--;
    return OK;
}

/** remove given element from given list (O(N)).
 * implies the user has given a comparison function.
 * @param l the list to remove the element from
 * @param e the element to remove
 * @return ERRABSENT if element is not found in list
 * @return ERRUNABLE if no comparison function has been provided
 * @return OK otherwise
 */
status 	remFromList	(List* l, void* e)
{
    if (!l->comp)
        return ERRUNABLE;
    Node* temp = l->head;
    int compRes = l->comp(e, temp->val);
    if (compRes == 0)
    {

        l->head = temp->next;
        free(temp);
        temp = 0;
        l->nelts--;
        return OK;
    }
    while (temp->next)
    {
        compRes = l->comp(e, temp->next->val);
        if (compRes == 0)
            break;
        temp = temp->next;
    }
    if (!temp->next)
        return ERRABSENT;
    Node* toRemove = temp->next;
    temp->next = temp->next->next;
    free(toRemove);
    toRemove = 0;
    l->nelts--;
    return OK;
}

/** display list elements as "[ e1 ... eN ]" (O(N)).
 * The display of the element is delegated to the prFun function
 * @param l the list to display.
 * @return OK otherwise
*/
status 	displayList	(List* l)
{
    if (!l->pr)
        return ERRUNABLE;
    Node* temp = l->head;
    while (temp)
    {
        l->pr(temp->val);
        temp = temp->next;
    }
    return OK;
}

/** sequencially call given function with each element of given list (O(NxF)).
 * @param l the list
 * @param f the function
 */
void	forEach		(List* l,void(*f)(void*))
{
    Node* temp = l->head;
    while(temp)
    {
        f(temp->val);
        temp = temp->next;
    }
}
/** compute and return the number of elements in given list (O(1)).
 * @param l the list
 * @return the number of elements in given list
 */
int	lengthList	(List* l)
{
    return l->nelts;
}

/** add given element to given list according to compFun function (O(N)).
 * @param l the list (supposedly sorted according to compFun function)
 * @param e the element to add
 * @return ERRALLOC if memory allocation failed
 * @return ERRUNABLE if no comparison function has been provided
 * @return OK otherwise
 */
status	addList	(List* l, void* e)
{
    if (!l->comp)
        return ERRUNABLE;
    Node* newVal = (Node*)malloc(sizeof(Node));
    if (!newVal)
        return ERRALLOC;
    Node* temp = l->head;
    if (!temp || l->comp(temp->val, e) >= 0)
    {
        newVal->next = temp;
        newVal->val = e;
        l->head = newVal;
        l->nelts++;
        return OK;
    }
    if (temp->next)
    {
        while ((temp->next) && (l->comp(temp->next->val, e) < 0))
            temp = temp->next;
    }
    newVal->next = temp->next;
    newVal->val = e;
    temp->next = newVal;
    l->nelts++;
    return OK;
}

/** tests whether the list contains given element (O(N)).
 * @param l the list
 * @param e the searched element
 * @return 0 if element is not found in list
 * @return 1 if element is at the head of the list (no predecessor)
 * @return (a pointer to) the predecessor of the search element otherwise
 */
Node*	isInList	(List* l, void* e)
{
    if (!l->comp)
        return 0;
    Node* temp = l->head;
    if (!temp)
        return 0;
    if (l->comp(temp->val, e) == 0)
        return (void*) 1;
    while (temp->next && l->comp(temp->next->val, e) != 0)
            temp = temp->next;
    if (!temp->next)
        return 0;
    return temp;
}

/** finds the first element that matches the predicate
 * @param l the list
 * @param f the predicate
 * @return 0 if no matching element was found
 * @return (a pointer to) the first that matches otherwise
 */
void* firstThat (List* l, int(*f)(void*))
{
    if (!f)
        return 0;
    Node* temp = l->head;
    while (temp)
    {
        if (f(temp->val))
            break;
        temp = temp->next;
    }
    if (!temp)
        return 0;
    return temp->val;
}
/** finds all elements that match the predicate
 * @param l the list
 * @param f the predicate
 * @return the list of all elements that match
 */
List* allThat (List* l, int(*f)(void*))
{
    if (!f)
        return 0;
    List* matchList = newList(l->comp, l->pr);
    Node* temp = l->head;
    while(temp)
    {
        if (f(temp->val))
            addList(matchList, temp->val);
        temp = temp->next;
    }
    return matchList;
}

