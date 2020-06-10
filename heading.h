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

 /**
  * Create a heading
  * @param word a pointer to the word of the heading
  * @return a pointer to the heading. Returns NULL if memory could not be allocated
  */
Heading *createHeading(char* word);

/**
 * Delete heading and free memory
 * @param heading a pointer to the heading
 */
void deleteHeading(void* heading);

/**
 * @category Capacity
 */

/**
 * Get the number of reference of the heading
 * @param heading a pointer to the heading
 * @return a size_t the number of pages
 */
size_t getNumberOfPage(const Heading* heading);


/**
 * @category Element access
 */

/**
 * Get the a pointer to the demanded page
 * @param heading a pointer to the heading
 * @param page an integer, the page number to get
 * @return a pointer to the page value if it exist. A NULL pointer otherwise.
 */
int* getPage(Heading* heading, int page);

/**
 * Get the value of the last page
 * @param heading a pointer to the heading
 * @return an integer, the value of the last page. 0 if page list is empty.
 */
int getLastPage(Heading* heading);

/**
 * Get the word of the heading
 * @param heading a pointer to the heading
 * @return a const char pointer to the word.
 */
const char* getHeadingWord(void* heading);

/**
 * @category Modifier
 */

/**
 * add an entry to the heading location at the end
 * @param heading a pointer to the heading
 * @param page an integer, the page to add
 * @return true if the insertion has been effectuated. False otherwise.
 */
bool addPage(Heading* heading, int page);

/**
 * add an entry to the heading location at the correct position
 * @param heading a pointer to the heading
 * @param page an integer, the page to add
 * @return true if the insertion has been effectuated. False otherwise.
 */
bool insertPageInPlace(Heading* heading, int page);

/**
 * Modify the word of the heading
 * @param heading a pointer to the heading
 * @param word a const char pointer to the new word
 */
void setHeadingWord(void* heading,char* word);

/**
 * @category Operation
 */

/**
 * Display the heading on the standard output
 * @param heading a pointer to the heading
 */
void displayHeading(const void* heading);

/**
 * @category Util functions
 */

/**
 * Comparison function for heading
 * @param a a void pointer to a heading
 * @param b a void pointer to a heading
 * @return an integral value indicating the relationship
 * between the two heading word
 * < 0  : the first character that does not match has a lower value in a than in b
 * 0    : the contents of both words are equal
 * >0   : the first character that does not match has a greater value in a than in b
 */
int compareHeading(const void* a, const void* b);

/**
 * Sort the location list
 * @param heading a pointer to a heading
 * @details sorted with a selection sort O(n²)
 */
void sortHeading(Heading* heading);



#endif //LABO_6_INDEXATION_HEADING_H
