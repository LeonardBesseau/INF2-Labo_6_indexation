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
    char* word;
    List* list;
};

Heading *createHeading(char* word){
    Heading *output = (Heading *) malloc(sizeof(Heading));
    if (output) {
        output->word = word;
        output->list = createEmptyList(VALUE);

        if (output->list){
            setDisplay(output->list, displayInt);
            setComparaison(output->list, compareInt);
            return output;
        }
    } else {
        return NULL;
    }
}

void destroyHeading(void* heading){
    if (heading){
        deleteList(((Heading*)  (heading))->list);
        free(heading);
    }
}

bool addPage(Heading* heading, int page){
    return pushValueBack(heading->list,page);
}

size_t getNumberOfPage(Heading* heading){
    return listSize(heading->list);
}

void displayHeading(const void* heading){
    printf("%s, ", ((Heading*)  (heading))->word);
    displayList(((Heading*)  (heading))->list);
    printf("\n");
}

char* getHeadingWord(void* heading){
    return ((Heading*)  (heading))->word;
}

int compareHeading(const void* a, const void* b){
    const Heading *A = a, *B = b;
    return strcmp(A->word, B->word);
}

void sortHeading(Heading* heading){
    sortList(heading->list);
}

