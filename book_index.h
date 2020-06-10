//
// Created by leonard on 6/2/20.
//

#ifndef LABO_6_INDEXATION_BOOK_INDEX_H
#define LABO_6_INDEXATION_BOOK_INDEX_H

#include <stdbool.h>


typedef struct ListIndex Index;

Index *createIndex();

bool analyseLine(Index *index, Index *stopWords, char *text, int* line);

void displayIndex(Index *index);

bool saveIndex(Index *index);

void deleteIndex(Index *index);

size_t getIndexSize(Index *index);

#endif //LABO_6_INDEXATION_BOOK_INDEX_H
