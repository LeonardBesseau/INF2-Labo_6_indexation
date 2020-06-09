#include <stdio.h>
#include <stdlib.h>
#include "read_file.h"
#define CHUNK 256

int read(void (*f)(char *string)) {
    const char* FICHIER = "/home/leonard/Downloads/macbeth.txt";
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