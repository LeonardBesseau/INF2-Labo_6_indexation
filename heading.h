//
// Created by leonard on 6/2/20.
//

#ifndef LABO_6_INDEXATION_HEADING_H
#define LABO_6_INDEXATION_HEADING_H

#include <stdbool.h>


typedef struct BookHeading Heading;


Heading *createHeading(const char* word);

void displayHeading(Heading* h);

bool addHeadingEntry(Heading *l, int value);

#endif //LABO_6_INDEXATION_HEADING_H
