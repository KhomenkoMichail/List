#include <stdio.h>

#include "listFunctions.h"
#include "structsAndConsts.h"

int main (void) {
    struct list lst = {};
    struct info listInfo = {};

    LIST_CTOR(lst, 5, listInfo);

    insortAfter (&lst, 0, 10);
    insortAfter (&lst, 1, 20);
    insortAfter (&lst, 2, 30);
    insortAfter (&lst, 3, 40);
    insortAfter (&lst, 2, 25);

    fprintfGraphDump2 (&lst, "graphDump.txt");
    return 0;

}
