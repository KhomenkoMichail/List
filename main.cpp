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
    InsertAfter(&lst, 1, 20, &dumpInfo);
    InsertAfter(&lst, 1, 20, &dumpInfo);
    InsertAfter(&lst, 2, 30, &dumpInfo);
    InsertBefore(&lst, 2, 14, &dumpInfo);
    DeleteElement(&lst, 1, &dumpInfo);
    DeleteElement(&lst, 5, &dumpInfo);
    InsertBeforeHead(&lst, 1, &dumpInfo);
    InsertBeforeHead(&lst, 1, &dumpInfo);
    InsertBeforeHead(&lst, 1, &dumpInfo);
    lst.nodeArr[6].prev = 8;
    lst.nodeArr[2].prev = 4;
    InsertBeforeHead(&lst, 1, &dumpInfo);
    InsertAfterTail(&lst, 99, &dumpInfo);

    return 0;
}
