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
#include <stdlib.h>
#include "string.h"
#include "index_list.h"


struct BookHeading {
    const char *word;
    IndexList *list;
};

Heading *createHeading(const char *word) {
    Heading *out = (Heading *) malloc(sizeof(Heading));
    if (out) {
        out->word = word;
        out->list = createEmptyIndexList(compareIndex);
        if (out->list) {
            return out;
        }
    }
    return NULL;
}

void displayHeading(Heading* h){
    printf("%s, ", h->word);
    displayIndexList(h->list);
}

bool addHeadingEntry(Heading *l, int value){
    return appendIndexList(l->list, value);
}