#include <stdio.h>

#include "listFunctions.h"
#include "structsAndConsts.h"
#include "classicListFunctions.h"
#include <stdlib.h>
#include <TXLib.h>

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

    struct dump dumpInfo = {};

    const char* nameOfDumpFile = "classicListDump.html";
    const char* nameOfTextGraphFile = "classicGraphDump.txt";

    dumpInfo.nameOfDumpFile = nameOfDumpFile;
    dumpInfo.nameOfGraphFile = nameOfTextGraphFile;
$$

    listNode_t* nullNode = classicListCtor();
$$
    dumpInfo.fictitiousNode = nullNode;
    $$
    printf("nullNode == %p\n", nullNode);
    listNode_t* node1 = ClassicInsertAfter(nullNode, 10, &dumpInfo);
    $$
    listNode_t* node2 = ClassicInsertAfter(node1, 20, &dumpInfo);
    $$
    listNode_t* node3 = ClassicInsertAfter(node2, 30, &dumpInfo);
    $$
    listNode_t* node4 = ClassicInsertAfter(node3, 40, &dumpInfo);
    $$
    listNode_t* node5 = ClassicInsertAfter(node4, 50, &dumpInfo);
    $$
    listNode_t* node6 = ClassicInsertAfter(node5, 60, &dumpInfo);
    $$
    ClassicInsertAfter(node6, 70, &dumpInfo);
    $$
    ClassicDeleteNode (node3, &dumpInfo);
    $$
    classicListDtor(nullNode);
$$

    return 0;
}
