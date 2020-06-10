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

int checkFileExist(const char *fileName);

int read(const char *fileName, bool (*f)(Index *index, Index *stopWords, char *word, int *line), Index *index,
         Index *stopWords);

int checkFileExist(const char *fileName) {
    FILE *file;

    file = fopen(fileName, "r");
    if (file) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

int read(const char *fileName, bool (*f)(Index *index, Index *stopWords, char *word, int *line), Index *index,
         Index *stopWords) {
    FILE *file;

    file = fopen(fileName, "r");
    if (file) {
        char *buf = malloc(CHUNK);

        if (buf == NULL) {
            return EXIT_ALLOCATION_FAILURE;
        }
        int line = 0;
        while (fgets(buf, CHUNK, file)) {
            if (buf[0] == '\n') {
                ++line;
                continue;
            }
            if (!f(index, stopWords, buf, &line)) {
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


int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Argument count invalid");
        return EXIT_FAILURE;
    }
    if (argc == 2) {
        if (argv[1][0] == '-') {
            printf("No help for you");
            return EXIT_SUCCESS;
        } else{
            fprintf(stderr, "Wrong argument");
            return EXIT_FAILURE;
        }
    }
    if (checkFileExist(argv[1])) {
        fprintf(stderr, "Input file doesn't exist");
        return EXIT_FAILURE;
    }
    if (!checkFileExist(argv[2])) {
        char ch = ' ';
        do {
            if (ch != '\n'){
                printf("Output file already exist.\nDo you want to overwrite it ? y/n");
            }
            ch = getchar();
        } while ( ch != 'y' && ch != 'n');
        if (ch == 'n') {
            return EXIT_FAILURE;
        }
    }


    Index *stopWords = createIndex();
    if (argc == 4){
        if (checkFileExist(argv[3])) {
            fprintf(stderr, "Stopwords file doesn't exist");
            deleteIndex(stopWords);
            return EXIT_FAILURE;
        }
        read(argv[3], analyseText, stopWords, NULL);
    }

    // "/home/leonard/Downloads/macbeth.txt" "/home/leonard/Downloads/stopwords.txt"
    //
    Index *index = createIndex();


    read(argv[1], analyseText, index, stopWords);
    displayIndex(index, stdout);

    printf("%zu", getIndexSize(index));
    if(!saveIndex(index,argv[2])){
        fprintf(stderr, "Error when writing to file");
    }

    deleteIndex(index);
    deleteIndex(stopWords);
    //*/
    return 0;
}