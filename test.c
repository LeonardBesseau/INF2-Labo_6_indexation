//
// Created by leonard on 6/5/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read_file.h"

char *strlwr(char *str) {
    unsigned char *p = (unsigned char *) str;

    while (*p) {
        *p = tolower((unsigned char) *p);
        p++;
    }

    return str;
}

void test2(char *string) {
    char *p = string;
    char *word = string;
    size_t line = 1;
    while (*p != '\0') {
        switch (*p) {
            case ' ':
                *p = '\0';
                printf("%zu %s\n",line, word);
                word = ++p;
                break;
            case '.':
            case ',':
            case '?':
            case '-':
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
}

void f (void **ptr, int* test){
    int * why = test;
    *ptr = test;
    int a = 2;
    ++a;
}

int main(void) {
    int c = 3;
    int* b = NULL;
    f(&b, &c);
    printf("%d",*b);
}
