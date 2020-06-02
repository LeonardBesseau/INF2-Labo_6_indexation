#include <stdio.h>
#include <stdlib.h>
#include "list.h"
int main() {
    List* a = createEmptyList();
    int test = 3;
    int test1 = 4;
    int test2 = 5;
    appendList(a, (void *) test);
    appendList(a, (void *) test1);
    appendList(a, (void *) test2);
    printf("%d", (int) (int*) listBegin(a));
    printf("%d", (int) (int*) listLast(a));
    printf("Hello, World!\n");
    deleteList(a);
    return 0;
}
