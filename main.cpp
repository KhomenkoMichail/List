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

    /*insortAfter2 (&lst, 0, 10);
    LIST_DUMP (&lst, dumpInfo, "WOW");
    insortAfter2 (&lst, 1, 20);
    LIST_DUMP (&lst, dumpInfo, "WOW");
    insortAfter2 (&lst, 2, 30);
    LIST_DUMP (&lst, dumpInfo, "WOW");
    insortAfter2 (&lst, 1, 15);
    LIST_DUMP (&lst, dumpInfo, "WOW");
    deleteElement2 (&lst, 2);
    //insortAfter (&lst, 2, 20);
    //insortAfter (&lst, 3, 20);
    //insortAfter (&lst, 4, 20);
    //deleteElement (&lst, 2);

    LIST_DUMP (&lst, dumpInfo, "WOW");
    deleteElement2 (&lst, 1);
    LIST_DUMP (&lst, dumpInfo, "WOW");*/

    InsortAfter(&lst, 0, 10, &dumpInfo);
    DeleteElement(&lst, 1, &dumpInfo);
    InsortAfter(&lst, 0, 10, &dumpInfo);
    InsortAfter(&lst, 1, 20, &dumpInfo);
    InsortAfter(&lst, 2, 30, &dumpInfo);
    InsortAfter(&lst, 3, 40, &dumpInfo);
    InsortAfter(&lst, 4, 50, &dumpInfo);
    InsortAfter(&lst, 5, 60, &dumpInfo);
    InsortAfter(&lst, 6, 70, &dumpInfo);
    InsortAfter(&lst, 7, 80, &dumpInfo);
    InsortAfter(&lst, 8, 90, &dumpInfo);

    return 0;
}
