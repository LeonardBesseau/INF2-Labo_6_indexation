#include <stdio.h>
#include <stdlib.h>
#include "read_file.h"

int read(void (*f)(char *string)) {


    const char* FICHIER = "/home/leonard/Downloads/macbeth.txt";

    #define CHUNK 256 /* read 1024 bytes at a time */
    char buf[CHUNK];
    FILE *file;
    size_t nread;

    file = fopen(FICHIER, "r");
    if (file) {
        char *buf = malloc(CHUNK);

        if (buf == NULL) {
            /* deal with malloc() failure */
        }

        while (fgets(buf, CHUNK, file)) {
            f((char *) buf);
        }
        if (ferror(file)) {
            /* deal with error */
        }
        fclose(file);
    }
    return EXIT_SUCCESS;
}