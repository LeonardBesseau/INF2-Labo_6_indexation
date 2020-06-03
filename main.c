#include <stdio.h>
#include <stdlib.h>
#include "index_list.h"
#include "heading.h"


int main() {
    IndexList* a = createEmptyIndexList(compareIndex);
    int arr[3] ={1,2,3};
    appendIndexList(a, arr[0]);
    appendIndexList(a, arr[1]);
    appendIndexList(a, arr[2]);
    printf("%d", indexListBegin(a));
    printf("%d", indexListLast(a));
    printf("%d", indexListContains(a, 4));
    deleteIndexList(a);
    return 0;
}
