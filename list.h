/* ---------------------------
Laboratoire : 6
Fichier : list.h
Auteur(s) : Besseau Cerottini Viotti
Date : 02-06-2020

But : Fournir une structure liste génerique pouvant contenir n'importe quel données

Remarque(s) :

Compilateur : gcc version 7.4.0

--------------------------- */
#ifndef LABO_6_INDEXATION_LIST_H
#define LABO_6_INDEXATION_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Type definition
 */
typedef struct LinkedList List;

/**
 * @category Constructor Destructor
 */

/**
 * Create an empty list
 * @return a pointer to the list. Returns NULL pointer if memory could not be allocated
 */
List *createEmptyList();

/**
 * Delete list and free memory
 * @param l a pointer to the list
 */
void deleteList(List *l);


/**
 * @category Capacity
 */

/**
 * Checks if list empty
 * @param l a pointer to the list
 * @return true if the list is empty. False otherwise
 */
bool isListEmpty(const List *l);

/**
 * Gets the number of element in the list
 * @param l a pointer to the list
 * @return a size_t the number of elements
 */
size_t listSize(const List *l);


/**
 * @category Element access
 */

/**
 * Access front element
 * @param l a pointer to the list
 * @return a void pointer to the data of the front element
 */
void *front(const List *l);

/**
 * Access front element
 * @param l a pointer to the list
 * @return a void pointer to the data of the front element
 */
void *back(const List *l);

/**
 * @category Modifier
 */

/**
 * Get an element form the list
 * @param l a pointer to the list
 * @param a a void pointer of the element of the list (Must be the same type as the list elements)
 * @return a pointer to the element in the list if it exist. A NULL pointer otherwise.
 */
void *getElement(List *l, const void *a);

/**
 * Add an element at the beginning of the list
 * @param l a pointer to the list
 * @param data a void pointer of the element to add.
 * @return true if the insertion has been effectuated. False otherwise.
 */
bool pushFront(List *l, void *data);

/**
 * Remove the first element
 * @param l a pointer to the list
 */
void pop_front(List *l);

/**
 * Add an element at the end of the list
 * @param l a pointer to the list
 * @param data a void pointer of the element to add.
 * @return true if the insertion has been effectuated. False otherwise.
 */
bool pushBack(List *l, void *data);

/**
 * Remove the last element
 * @param l a pointer to the list
 */
void pop_back(List *l);

/**
 * Add an element in place
 * @param l a pointer to the list
 * @param data a void pointer of the element to add.
 * @param out a void pointer to the data if already present
 * @return true if the insertion has been effectuated or was already present. False otherwise.
 * @attention Complexity O(N)
 */
bool insertInOrder(List *l, void *data, void** out);

/**
 * @category Operation
 */

/**
 * Display the list on the standard output
 * @param l a pointer to the list
 * @param separator a boolean, set to true to enable separator
 * @param output a pointer to the output
 */
void displayList(const List *l, bool separator, FILE* output);

/**
 * Sort the list
 * @param l a pointer to the list
 * @details sorted with a selection sort O(n²)
 */
void sortList(List *l);

/**
 * @category Util functions
 */


/**
 * Set the cleanup function to be used when destructing an element
 * @param l a pointer to the list
 * @param destroy a pointer to a function that cleans up the data
 */
void setCleanup(List *l, void (*destroy)(void *));

/**
 * Set the display function to be used when destructing an element
 * @param l a pointer to the list
 * @param display a pointer to a function that display the data
 */
void setDisplay(List *l, void (*display)(const void *, FILE*));

/**
 * Set the comparison function
 * @param l a pointer to the list
 * @param cmp a pointer to a function that compare the data between them
 */
void setCompare(List *l, int(*cmp)(const void *a, const void *b));


#endif //LABO_6_INDEXATION_LIST_H
