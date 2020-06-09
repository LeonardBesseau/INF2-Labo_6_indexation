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


void destroyInt(void* data);

int compareInt(const void* a, const void* b);

void displayInt(const void* a);

Heading *createHeading(char* word){
    Heading *output = (Heading *) malloc(sizeof(Heading));
    if (output) {
        output->word = word;
        output->list = createEmptyList();
        if (output->list){
            setCleanup(output->list, destroyInt);
            setDisplay(output->list, displayInt);
            setCompare(output->list, compareInt);
            return output;
        } else{
            free(output);
            return NULL;
        }
    } else {
        return NULL;
    }
}

void destroyHeading(void* heading){
    if (heading){
        deleteList(((Heading*) heading)->list);
        free(heading);
        heading = NULL;
    }
}

bool addPage(Heading* heading, int page){
    int* tmp = (int*) malloc(sizeof(int));
    *tmp = page;
    return pushBack(heading->list,tmp);
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
    const Heading *A = (Heading*) a, *B = (Heading *)b;
    return strcmp(A->word, B->word);
}

void sortHeading(Heading* heading){
    sortList(heading->list);
}

int* getPage(Heading* heading, int page){
    int* test = getElement(heading->list, &page);
    if (test){
        return test;
    } else{
        return NULL;
    }
}

void setHeadingWord(void* heading, char* word){
    ((Heading*) heading)->word = word;
}

int compareInt(const void *a, const void *b) {
    const int *A = a, *B = b;
    return (*A > *B) - (*A < *B);
}

void displayInt(const void *a) {
    const int *A = a;
    printf("%d, ", *A);
}

void destroyInt(void* data){
    if (data){
        free(data);
        data = NULL;
    }
}

