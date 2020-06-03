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


typedef struct LinkedIndexList IndexList;


IndexList *createEmptyIndexList(int (*cmp) (const int *, const int*));

void deleteIndexList(IndexList *l);

bool isIndexListEmpty(const IndexList *l);

bool appendIndexList(IndexList *l, int value);

int indexListBegin(const IndexList *l);

int indexListLast(const IndexList *l);

bool indexListContains(const IndexList *l, int value);

int compareIndex(const int* lhs, const int* rhs);

void displayIndexList(const IndexList *l);

#endif //LABO_6_INDEXATION_INDEX_LIST_H
