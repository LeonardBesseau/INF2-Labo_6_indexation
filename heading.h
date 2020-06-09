//
// Created by leonard on 6/2/20.
//

#ifndef LABO_6_INDEXATION_HEADING_H
#define LABO_6_INDEXATION_HEADING_H
#include "list.h"
typedef struct BookHeading Heading;

/**
 * @category Constructor Destructor
 */
Heading *createHeading(char* word);

void destroyHeading(void* heading);

/**
 * @category Capacity
 */

size_t getNumberOfPage(Heading* heading);

bool addPage(Heading* heading, int page);


void displayHeading(const void* heading);

char* getHeadingWord(void* heading);

void setHeadingWord(void* heading, char* word);

int compareHeading(const void* a, const void* b);

void sortHeading(Heading* heading);

int* getPage(Heading* heading, int page);

int* getLastPage(Heading* heading, int page);

#endif //LABO_6_INDEXATION_HEADING_H
