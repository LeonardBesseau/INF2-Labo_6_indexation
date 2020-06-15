/* ---------------------------
Laboratoire :
Fichier : book_index.h
Auteur(s) : Besseau
Date : 15-06-2020

But : Fournir une structure listant des headings afin de génerer l'index d'un texte

Remarque(s) :

Compilateur : gcc version 7.4.0

--------------------------- */

#ifndef LABO_6_INDEXATION_BOOK_INDEX_H
#define LABO_6_INDEXATION_BOOK_INDEX_H

#include <stdbool.h>
#include <stdio.h>

typedef struct ListIndex Index;

/**
 * @category Constructor Destructor
 */

/**
 * Create an empty index
 * @return a pointer to the list. Returns NULL pointer if memory could not be allocated
 */
Index *createIndex();

/**
 * Delete index and free memory
 * @param index
 */
void deleteIndex(Index *index);

/**
 * @category Capacity
 */

/**
 * Gets the number of element in the list
 * @param index a pointer to the index
 * @return a size_t the number of elements
 */
size_t getIndexSize(Index *index);


/**
 * Analyse a text and extracts its word into the index
 * @param index a pointer to the index in which the words are added
 * @param stopWords a pointer to an index in which forbidden words are stored (Can be null or empty if need be)
 * @param text the text to analyse. Can be composed of multiple lines
 * @param line a pointer to an integer. The starting line of the text
 * @return true if the operation succeed. false otherwise.
 */
bool analyseText(Index *index, Index *stopWords, char *text, int* line);

/**
 * Display index on a given output
 * @param index a pointer to the index to display
 * @param file the output to write on
 */
void displayIndex(Index *index, FILE *file);

/**
 * Save the index into a file
 * @param index a pointer to the index
 * @param fileName a char pointer to the name of the file. (Must be writable)
 * @return true if the operation succeed. false otherwise.
 */
bool saveIndex(Index *index, const char *fileName);

/**
 *
 * @param filename the name of the file to read
 * @param index the index in which to add the heading
 * @param stopWords the index containing excluded word
 * @return EXIT_SUCCESS if the operation succeeded. EXIT_FAILURE otherwise.
 */
int addToIndexFromFiles(const char *filename, Index *index, Index *stopWords);


#endif //LABO_6_INDEXATION_BOOK_INDEX_H
