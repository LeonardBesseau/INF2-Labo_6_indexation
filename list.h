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


typedef struct LinkedList List;
typedef struct LinkedNode Node;

List *createEmptyList();

void deleteList(List *l);

bool isListEmpty(List *l);

bool appendList(List *l, void *value);

void *listBegin(List *l);

void *listLast(List *l);

#endif //LABO_6_INDEXATION_LIST_H
