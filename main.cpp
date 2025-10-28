#include <stdio.h>

#include "listFunctions.h"
#include "structsAndConsts.h"
#include <stdlib.h>
//#include "TXLib.h"

int main (void) {
    struct list lst = {};
    struct info listInfo = {};
    //struct info dumpInfo = {};

    struct dump dumpInfo = {};
    dumpInfo.nameOfTextGraphFile = "graphDump.txt";
    dumpInfo.nameOfHTMLFile = "listDump.html";

    LIST_CTOR(lst, 5, listInfo, dumpInfo);

    insortAfter (&lst, 0, 10);
    insortAfter (&lst, 1, 20);
    insortAfter (&lst, 2, 20);
    insortAfter (&lst, 3, 20);
    insortAfter (&lst, 4, 20);
    deleteElement (&lst, 2);
    //$$

    //FILE* file = fopen("listDump.html", "w");
    LIST_DUMP (&lst, dumpInfo);
    fclose(dumpInfo.HTMLFilePtr);
    return 0;

}
