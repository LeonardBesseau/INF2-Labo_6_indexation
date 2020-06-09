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

void *front(const List *l);

void *back(const List *l);

List *createEmptyList();

bool isListEmpty(const List *l);

size_t listSize(const List *l);

bool pushFront(List *l, void *data);

bool pushBack(List *l, void *data);

void pop_front(List *l);

void pop_back(List *l);

void deleteList(List* l);

void setCleanup(List *l, void (*destroy) (void*));

void setDisplay(List* l, void (*display) (const void*));

void setCompare(List* l, int(*cmp) (const void* a, const void* b));

void displayList(List *l);

void* getElement(List* l, const void*a);

void sortList(List* l);





#endif //LABO_6_INDEXATION_LIST_H
