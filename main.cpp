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

    insortAfter2 (&lst, 0, 10);
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
    LIST_DUMP (&lst, dumpInfo, "WOW");

    return 0;
}
