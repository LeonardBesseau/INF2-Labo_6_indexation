#include <ctype.h>
#include <string.h>

#include "book_index.h"
#include "heading.h"
#include "list.h"

struct ListIndex {
    List* list;
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

bool analyseString(List * index, char* string);

bool analyseString(List * index, char* string){
    char *p = string;
    char *word = string;
    size_t line = 1;
    while (*p != '\0') {
        switch (*p) {
            case ' ':
                *p = '\0';
                if (strlen(word) >= 3) {
                    Heading *heading = createHeading(strlwr(word));
                    if(heading){
                        Heading *ptr = getElement(index, heading);
                        if (ptr) {
                            int* page = getPage(ptr, line);
                            if (!page){
                                addPage(ptr, line);
                            }
                            destroyHeading(heading);
                        } else {
                            addPage(heading, line);
                            pushBack(index, heading);
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
            case ',':
            case '?':
            case '-':
            case '!':
            case ';':
            case ':':
            case '\'':
            case '\"':
                *p = ' ';
                break;
            case '\n':
                *p = ' ';
                ++line;
                break;
            default:
                ++p;
        }
    }
    return true;
}

Index *createIndex() {
    Index* index = (Index *) malloc(sizeof(Index));
    index->list = createEmptyList();
    if (index->list) {
        setDisplay(index->list, displayHeading);
        setCleanup(index->list, destroyHeading);
        setCompare(index->list, compareHeading);
    }
    return index;
}

bool analyseLine(Index *index, char *line){
    return analyseString(index->list, line);
}

void displayIndex(Index *index){
    sortList(index->list);
    displayList(index->list);
}

bool saveIndex(Index *index){
    return false;
}

void deleteIndex(Index *index){
    deleteList(index->list);
    free(index);
}

size_t getIndexSize(Index* index){
    return listSize(index->list);
}

