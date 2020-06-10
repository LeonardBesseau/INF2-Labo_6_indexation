#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "heading.h"
#include "book_index.h"

#define EXIT_ALLOCATION_FAILURE 2
#define EXIT_FILE_MISSING 3
#define EXIT_FILE_READ 4
#define EXIT_ERROR_ANALYSE 5
#define CHUNK 256

int read(const char* fileName, bool (*f)(Index *index, Index *stopWords, char *word, int* line), Index* index, Index* stopWords) {
    const char *FILE_NAME = fileName;
    FILE *file;

    file = fopen(FILE_NAME, "r");
    if (file) {
        char *buf = malloc(CHUNK);

        if (buf == NULL) {
            return EXIT_ALLOCATION_FAILURE;
        }
        int line = 0;
        while (fgets(buf, CHUNK, file)) {
            if(buf[0] == '\n'){
                ++line;
                continue;
            }
            if(!f(index, stopWords, buf, &line)){
                free(buf);
                return EXIT_ERROR_ANALYSE;
            }
            free(buf);
            buf = malloc(CHUNK);
            if (buf == NULL) {
                return EXIT_ALLOCATION_FAILURE;
            }
        }
        free(buf);
        if (ferror(file)) {
            return EXIT_FILE_READ;
        }
        fclose(file);
    } else {
        printf("Sorry, file doesn't exist.");
        return EXIT_FILE_MISSING;
    }
    return EXIT_SUCCESS;
}

int main() {
//*


    Index * index = createIndex();
    Index * stopWords = createIndex();
    read("/home/leonard/Downloads/stopwords.txt",analyseLine, stopWords, NULL);
    read("/home/leonard/Downloads/macbeth.txt",analyseLine, index, stopWords);
    displayIndex(index);

    printf("%zu", getIndexSize(index));

    deleteIndex(index);
    deleteIndex(stopWords);
    //*/
    return 0;
}