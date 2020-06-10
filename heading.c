/* ---------------------------
Laboratoire :
Fichier : heading.c
Auteur(s) : Besseau
Date : 02-06-2020

But :

Remarque(s) :

Compilateur : gcc version 7.4.0

--------------------------- */
#include "heading.h"
#include <stdio.h>
#include <string.h>

struct BookHeading {
    char *word;
    List *location;
};


void destroyInt(void *data);

int compareInt(const void *a, const void *b);

void displayInt(const void *a);

Heading *createHeading(char *word) {
    Heading *output = malloc(sizeof(Heading));
    if (output) {
        size_t size = strlen(word) + 1;
        output->word = malloc(size);
        if (output->word) {
            memcpy(output->word, word, size);
            output->location = createEmptyList();
            if (output->location) {
                setCleanup(output->location, destroyInt);
                setDisplay(output->location, displayInt);
                setCompare(output->location, compareInt);
                return output;
            }
            free(output->word);
        }
        free(output);
    }
    return NULL;
}

void deleteHeading(void *heading) {
    if (heading) {
        deleteList(((Heading *) heading)->location);
        free(((Heading *) heading)->word);
        free(heading);
        heading = NULL;
    }
}

bool addPage(Heading *heading, int page) {
    int *tmp = malloc(sizeof(int));
    *tmp = page;
    return pushBack(heading->location, tmp);
}

bool insertPageInPlace(Heading *heading, int page) {
    int *tmp = malloc(sizeof(int));
    *tmp = page;
    return insertInOrder(heading->location, tmp, NULL);
}

size_t getNumberOfPage(const Heading *heading) {
    return listSize(heading->location);
}

void displayHeading(const void *heading) {
    printf("%s, ", ((Heading *) (heading))->word);
    displayList(((Heading *) (heading))->location, true);
}

const char *getHeadingWord(void *heading) {
    return ((Heading *) (heading))->word;
}

int compareHeading(const void *a, const void *b) {
    const Heading *A = (Heading *) a, *B = (Heading *) b;
    return strcmp(A->word, B->word);
}

void sortHeading(Heading *heading) {
    sortList(heading->location);
}

int *getPage(Heading *heading, int page) {
    int *test = getElement(heading->location, &page);
    if (test) {
        return test;
    } else {
        return NULL;
    }
}

int getLastPage(Heading *heading) {
    int *test = back(heading->location);
    if (test) {
        return *test;
    } else {
        return 0;
    }
}

void setHeadingWord(void *heading, char *word) {
    ((Heading *) heading)->word = word;
}

int compareInt(const void *a, const void *b) {
    const int *A = a, *B = b;
    return (*A > *B) - (*A < *B);
}

void displayInt(const void *a) {
    const int *A = a;
    printf("%d", *A);
}

void destroyInt(void *data) {
    if (data) {
        free(data);
        data = NULL;
    }
}

