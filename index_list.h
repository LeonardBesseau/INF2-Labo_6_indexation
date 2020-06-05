/* ---------------------------
Laboratoire :
Fichier : list.h
Auteur(s) : Besseau
Date : 02-06-2020

But :

Remarque(s) :

Compilateur : gcc version 7.4.0

--------------------------- */
#ifndef LABO_6_INDEXATION_INDEX_LIST_H
#define LABO_6_INDEXATION_INDEX_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "heading_decl.h"

typedef struct LinkedList List;

typedef enum {
    VALUE, HEADING
} Type;

int frontValue(const List *l);

int backValue(const List *l);

Heading *frontHeading(const List *l);

Heading *backHeading(const List *l);

List *createEmptyList(Type type);

bool isListEmpty(const List *l);

size_t listSize(const List *l);

bool pushValueFront(List *l, int value);

bool pushHeadingFront(List *l, Heading *heading);

bool pushValueBack(List *l, int value);

bool pushHeadingBack(List *l, Heading *heading);

void pop_front(List *l);

void pop_back(List *l);

void deleteList(List* l);

#endif //LABO_6_INDEXATION_INDEX_LIST_H
