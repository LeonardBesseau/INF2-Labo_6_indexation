#include <ctype.h>
#include <string.h>
#include "book_index.h"
#include "heading.h"
#include "list.h"


#define CHUNK 256

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
                            if (insertInOrder(index, heading, (void **) &ptr)) {
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
            case '|':
            case '_':
            case '[':
            case ']':
            case '#':
            case '<':
            case '>':
            case '@':
            case '`':
            case '(':
            case ')':
            case '*':
            case '"':
            case ',':
            case '=':
            case '/':
            case '?':
            case '-':
            case '!':
            case ';':
            case ':':
            case '\'':
                *p = ' ';
                break;
            case '\n':
                if (*(p + 1) != '\n') {
                    ++line;
                }
                *p = ' ';
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

bool analyseText(Index *index, Index *stopWords, char *text, int* line) {
    if (stopWords){
        return analyseString(index->list, stopWords->list, text, line);
    }else{
        return analyseString(index->list, NULL, text, line);
    }

}

void displayIndex(Index *index, FILE* file) {
    displayList(index->list, false, file);
}

bool saveIndex(Index *index, const char* fileName) {
    FILE *file;

    file = fopen(fileName, "w");
    if (file) {
        displayList(index->list, false, file);
        if (ferror(file)) {
            fprintf(stderr, "Error writing to file");
            return false;
        }
    } else{
        return false;
    }
    fclose(file);
    return true;
}

void deleteIndex(Index *index) {
    deleteList(index->list);
    free(index);
}

size_t getIndexSize(Index *index) {
    return listSize(index->list);
}

int addToIndexFromFiles(const char *fileName, Index *index, Index *stopWords) {
    FILE *file;

    file = fopen(fileName, "r");
    if (file) {
        char *buf = malloc(CHUNK);

        if (buf == NULL) {
            return EXIT_FAILURE;
        }
        int line = 0;
        while (fgets(buf, CHUNK, file)) {
            ++line;
            if (buf[0] == '\n') {
                continue;
            }
            if (!analyseText(index, stopWords, buf, &line)) {
                free(buf);
                return EXIT_FAILURE;
            }
            free(buf);
            buf = malloc(CHUNK);
            if (buf == NULL) {
                return EXIT_FAILURE;
            }
        }
        free(buf);
        if (ferror(file)) {
            return EXIT_FAILURE;
        }
        fclose(file);
    } else {
        fprintf(stderr, "Sorry, file doesn't exist.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

