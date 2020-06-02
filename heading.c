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

struct BookHeading {
    char* word;
    List* list;
};

Heading* createHeading(char* word){
    Heading *output = malloc(sizeof(Heading));
    if (output){
        output->word =word;
        output->list = createEmptyList();
    } else{
        return NULL;
    }
}