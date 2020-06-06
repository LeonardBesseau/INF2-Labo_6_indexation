/* ---------------------------
Laboratoire :
Fichier : list.h
Auteur(s) : Besseau
Date : 02-06-2020

But :

Remarque(s) :

Compilateur : gcc version 7.4.0

--------------------------- */
#ifndef LABO_6_INDEXATION_LIST_H
#define LABO_6_INDEXATION_LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct LinkedList List;

typedef enum {
    VALUE, HEADING
} Type;

int frontValue(const List *l);

int backValue(const List *l);

void *frontHeading(const List *l);

void *backHeading(const List *l);

List *createEmptyList(Type type);

bool isListEmpty(const List *l);

size_t listSize(const List *l);

bool pushValueFront(List *l, int value);

bool pushHeadingFront(List *l, void *heading);

bool pushValueBack(List *l, int value);

bool pushHeadingBack(List *l, void *heading);

void pop_front(List *l);

void pop_back(List *l);

void deleteList(List* l);

void setHeadingCleanup(List *l, void (*destroy) (void*));

void setDisplay(List* l, void (*display) (const void*));

void setComparaison(List* l, int(*cmp) (const void* a, const void* b));

void displayList(List *l);

void* findHeading(const List* l, char* word);

int compareInt(const void* a, const void* b);

void displayInt(const void* a);

void* getElement(List* l, const void*a);

void sortList(List* l);



#endif //LABO_6_INDEXATION_LIST_H
