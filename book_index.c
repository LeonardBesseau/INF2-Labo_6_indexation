#include <ctype.h>
#include <string.h>

#include "book_index.h"
#include "heading.h"
#include "list.h"

struct ListIndex {
    List *list;
};


char *strlwr(char *str);

char *strlwr(char *str) {
    unsigned char *p = (unsigned char *) str;

    while (*p) {
        *p = tolower((unsigned char) *p);
        p++;
    }

    return str;
}

bool analyseString(List *index, List *stopWords, char *string, int* line);

bool analyseString(List *index, List *stopWords, char *string, int* line) {
    char *p = string;
    char *word = string;
    while (*p != '\0') {
        switch (*p) {
            case ' ':
                *p = '\0';
                if (strlen(word) >= 3) {
                    Heading *ptr = NULL;
                    Heading *heading = createHeading(strlwr(word));
                    if (heading){
                        Heading *forbidden = stopWords ? getElement(stopWords, heading) : NULL;
                        if (forbidden){
                            deleteHeading(heading);
                        }else{
                            if (insertInOrder(index, heading, &ptr)) {
                                if (ptr) {
                                    if (getLastPage(ptr) != *line) {
                                        addPage(ptr, *line);
                                    }
                                    deleteHeading(heading);
                                } else {
                                    addPage(heading, *line);
                                }
                            } else {
                                deleteHeading(heading);
                                return false;
                            }
                        }
                    }else{
                        return false;
                    }
                }
                word = ++p;
                break;
            case '.':
            case '[':
            case ']':
            case '<':
            case '(':
            case ')':
            case '"':
            case ',':
            case '?':
            case '-':
            case '!':
            case ';':
            case ':':
            case '\'':
                *p = ' ';
                break;
            case '\n':
                *p = ' ';
                (*line)++;
                break;
            default:
                ++p;
        }
    }
    return true;
}

Index *createIndex() {
    Index *index = malloc(sizeof(Index));
    index->list = createEmptyList();
    if (index->list) {
        setDisplay(index->list, displayHeading);
        setCleanup(index->list, deleteHeading);
        setCompare(index->list, compareHeading);
    }
    return index;
}

bool analyseLine(Index *index, Index *stopWords, char *word, int* line) {
    if (stopWords){
        return analyseString(index->list, stopWords->list, word, line);
    }else{
        return analyseString(index->list, NULL, word, line);
    }

}

void displayIndex(Index *index) {
    sortList(index->list);
    displayList(index->list, false);
}

bool saveIndex(Index *index) {
    return false;
}

void deleteIndex(Index *index) {
    deleteList(index->list);
    free(index);
}

size_t getIndexSize(Index *index) {
    return listSize(index->list);
}

