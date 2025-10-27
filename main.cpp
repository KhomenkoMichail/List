#include <stdio.h>

#include "listFunctions.h"
#include "structsAndConsts.h"
#include <stdlib.h>

int main (void) {
    struct list lst = {};
    struct info listInfo = {};
    struct info dumpInfo = {};

    LIST_CTOR(lst, 5, listInfo);

    insortAfter (&lst, 0, 10);
    insortAfter (&lst, 1, 20);

    FILE* file = fopen("listDump.html", "w");
    LIST_DUMP (&lst, dumpInfo, file, "graphDump.txt");
    fclose(file);
    return 0;

}
