/* ---------------------------
Laboratoire : 6
Fichier : main.c
Auteur(s) : Besseau Cerottini Viotti
Date : 15-06-2020

But : Programme fournissant une ligne de commande pour générer l'index d'un texte

Remarque(s) :

Compilateur : gcc version 7.4.0

--------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_index.h"

/**
 * Verify if a filename exist
 * @param fileName path to the filename
 * @return EXIT_SUCCESS if file exist. EXIT_FAILURE otherwise
 */
int checkFileExist(const char *fileName);

int checkFileExist(const char *fileName) {
    FILE *file;

    file = fopen(fileName, "r");
    if (file) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Argument count invalid");
        return EXIT_FAILURE;
    }
    if (argc == 2) {
        if (strlen(argv[1]) != 2 && argv[1][0] != '-' && argv[1][1] != 'h') {
            fprintf(stderr, "Wrong argument");
            return EXIT_FAILURE;
        } else {
            printf("Usage : index INDEX FILE OUTPUT FILE [STOPWORDS FILE]\n");
            printf("\t-h display help");
            return EXIT_SUCCESS;
        }
    }
    if (checkFileExist(argv[1])) {
        fprintf(stderr, "Input file doesn't exist");
        return EXIT_FAILURE;
    }
    if (!checkFileExist(argv[2])) {
        char ch = ' ';
        do {
            if (ch != '\n') {
                printf("Output file already exist.\nDo you want to overwrite it ? y/n");
            }
            ch = getchar();
        } while (ch != 'y' && ch != 'n');
        if (ch == 'n') {
            return EXIT_FAILURE;
        }
    }

    Index *stopWords = createIndex();
    if (argc == 4) {
        if (checkFileExist(argv[3])) {
            fprintf(stderr, "Stopwords file doesn't exist");
            deleteIndex(stopWords);
            return EXIT_FAILURE;
        }
        if (addToIndexFromFiles(argv[3], stopWords, NULL)) {
            deleteIndex(stopWords);
            fprintf(stderr, "An error occurred during the proccess");
        }

    }

    Index *index = createIndex();
    if (addToIndexFromFiles(argv[1], index, stopWords)) {
        deleteIndex(stopWords);
        deleteIndex(index);
        fprintf(stderr, "An error occurred during the proccess");
    }
    displayIndex(index, stdout);

    printf("%zu", getIndexSize(index));
    if (!saveIndex(index, argv[2])) {
        fprintf(stderr, "Error when writing to file");
    }

    deleteIndex(index);
    deleteIndex(stopWords);
    return EXIT_SUCCESS;
}