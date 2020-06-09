//
// Created by leonard on 6/2/20.
//

#ifndef LABO_6_INDEXATION_BOOK_INDEX_H
#define LABO_6_INDEXATION_BOOK_INDEX_H

#include "list.h"

List* createIndex();

bool analyseLine(List* index, char* line);

void displayIndex(List* index);

void saveIndex(List* index);

void deleteIndex(List* index);

#endif //LABO_6_INDEXATION_BOOK_INDEX_H
