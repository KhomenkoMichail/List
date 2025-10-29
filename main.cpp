#include <stdio.h>

#include "listFunctions.h"
#include "structsAndConsts.h"
#include <stdlib.h>


int main (void) {

    struct list lst = {};
    struct info listInfo = {};
    struct dump dumpInfo = {};

    const char* nameOfDumpFile = "listDump.html";
    const char* nameOfTextGraphFile = "graphDump.txt";

    dumpInfo.nameOfDumpFile = nameOfDumpFile;
    dumpInfo.nameOfGraphFile = nameOfTextGraphFile;

    LIST_CTOR(lst, 5, listInfo);

    InsertAfter(&lst, 0, 10, &dumpInfo);
    insertBefore(&lst, 1, 99, &dumpInfo);
    InsertAfter(&lst, 1, 20, &dumpInfo);
    InsertAfter(&lst, 2, 60, &dumpInfo);
    InsertAfter(&lst, 3, 280, &dumpInfo);
    InsertAfter(&lst, 4, 7, &dumpInfo);
    InsertAfter(&lst, 5, 8, &dumpInfo);
    deleteElement(&lst, 4, &dumpInfo);



    return 0;
}
