#include "book_index.h"
#include "heading.h"

List *createIndex() {
    List *index = createEmptyList();
    if (index) {
        setDisplay(index, displayHeading);
        setCleanup(index, destroyHeading);
        setCompare(index, compareHeading);
    }
    return index;
}

bool analyseLine(List *index, char *line);

void displayIndex(List *index){
    displayList(index);
}

void saveIndex(List *index);

void deleteIndex(List *index){
    deleteList(index);
}

