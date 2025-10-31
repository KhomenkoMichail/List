#include <stdio.h>

#include "listFunctions.h"
#include "structsAndConsts.h"
#include "classicListFunctions.h"
#include <stdlib.h>


int main (void) {

/*
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
    lst.nodeArr[6].prev = 100;
    lst.nodeArr[2].prev = 90;
    InsertBeforeHead(&lst, 1, &dumpInfo);
    InsertAfterTail(&lst, 99, &dumpInfo);

    listDtor(&lst);*/

/*
    InsertAfter(&lst, 0, 100, &dumpInfo);
    InsertAfter(&lst, 1, 200, &dumpInfo);
    InsertAfter(&lst, 2, 300, &dumpInfo);
    InsertAfter(&lst, 3, 400, &dumpInfo);
    InsertAfter(&lst, 4, 500, &dumpInfo);
    InsertAfter(&lst, 5, 600, &dumpInfo);
    InsertAfter(&lst, 6, 700, &dumpInfo);
    InsertAfter(&lst, 7, 800, &dumpInfo);
    InsertAfter(&lst, 8, 900, &dumpInfo);
    InsertAfter(&lst, 9, 1000, &dumpInfo);
    lst.nodeArr[2].prev = 8;
    lst.nodeArr[8].next = 2;
    lst.nodeArr[4].prev = 6;
    lst.nodeArr[6].next = 4;
    InsertAfter(&lst, 10, 1100, &dumpInfo);
*/

/*
    InsertAfter(&lst, 0, 100, &dumpInfo);
    InsertAfter(&lst, 1, 200, &dumpInfo);
    InsertAfter(&lst, 2, 300, &dumpInfo);
    InsertAfter(&lst, 3, 400, &dumpInfo);
    InsertAfter(&lst, 4, 500, &dumpInfo);
    InsertAfter(&lst, 5, 600, &dumpInfo);
    InsertAfter(&lst, 6, 700, &dumpInfo);
    InsertAfter(&lst, 7, 800, &dumpInfo);
    InsertAfter(&lst, 8, 900, &dumpInfo);
    InsertAfter(&lst, 9, 1000, &dumpInfo);
    lst.nodeArr[2].next = 100;
    InsertAfter(&lst, 10, 1100, &dumpInfo);
*/
    //listDtor(&lst);*/


    listNode_t* nullNode = classicListCtor();
    listNode_t* firstNode = classicInsertAfter(nullNode, 10);
    listNode_t* secondNode = classicInsertAfter(firstNode, 20);
    listNode_t* thirdNode = classicInsertAfter(firstNode, 30);
    classicListGraphDump (nullNode, "classicGraph.txt");


    return 0;
}
