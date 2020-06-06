//
// Created by leonard on 6/2/20.
//

#ifndef LABO_6_INDEXATION_HEADING_H
#define LABO_6_INDEXATION_HEADING_H
#include "heading_decl.h"
#include "list.h"

Heading *createHeading(char* word);

void destroyHeading(void* heading);

bool addPage(Heading* heading, int page);

size_t getNumberOfPage(Heading* heading);

void displayHeading(const void* heading);

char* getHeadingWord(void* heading);

int compareHeading(const void* a, const void* b);

void sortHeading(Heading* heading);

#endif //LABO_6_INDEXATION_HEADING_H
