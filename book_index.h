//
// Created by leonard on 6/2/20.
//

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
 * @param stopWords a pointer to an index in which forbidden words are stored
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
void displayIndex(Index *index, FILE* file);

/**
 * Save the index into a file
 * @param index a pointer to the index
 * @param fileName a char pointer to the name of the file. (Must be writable)
 * @return true if the operation succeed. false otherwise.
 */
bool saveIndex(Index *index, const char* fileName);




#endif //LABO_6_INDEXATION_BOOK_INDEX_H
