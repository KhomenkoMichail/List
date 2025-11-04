#include <stdio.h>

#include "listFunctions.h"
#include "structsAndConsts.h"
#include "classicListFunctions.h"
#include <stdlib.h>
#include <TXLib.h>

int main (void) {


    struct list lst = {};
    struct info listInfo = {};
    struct dump dumpInfo = {};

    const char* nameOfDumpFile = "listDump.html";
    const char* nameOfTextGraphFile = "graphDump.txt";

    dumpInfo.nameOfDumpFile = nameOfDumpFile;
    dumpInfo.nameOfGraphFile = nameOfTextGraphFile;

    LIST_CTOR(lst, 20, listInfo);


    InsertAfter(&lst, 0, 10, &dumpInfo);
    InsertAfter(&lst, 1, 20, &dumpInfo);
    InsertAfter(&lst, 1, 20, &dumpInfo);
    InsertAfter(&lst, 2, 30, &dumpInfo);
    InsertBefore(&lst, 2, 40, &dumpInfo);
    DeleteElement(&lst, 1, &dumpInfo);
    DeleteElement(&lst, 5, &dumpInfo);
    InsertBeforeHead(&lst, 50, &dumpInfo);
    InsertAfter(&lst, 4, 50, &dumpInfo);
    InsertAfter(&lst, 2, 70, &dumpInfo);
    InsertBeforeHead(&lst, 60, &dumpInfo);
    InsertBeforeHead(&lst, 70, &dumpInfo);
    //lst.nodeArr[6].prev = 100;
    //lst.nodeArr[2].prev = 90;
    InsertBeforeHead(&lst, 80, &dumpInfo);
    InsertAfterTail(&lst, 90, &dumpInfo);
    DeleteElement(&lst, 3, &dumpInfo);
    DeleteElement(&lst, 4, &dumpInfo);
    //qsort((lst.nodeArr)+1, lst.capacity - 1, sizeof(struct node), &linearOrderNodeComparator);
    //listDump (&lst, &dumpInfo, "AFTER QSORT");
    if(!(*isListLinear(&lst)))
        MakeListLinear(&lst, &dumpInfo);

    listDtor(&lst);

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
/*
    struct classicList cList = {};
    struct dump dumpInfo = {};

    const char* nameOfDumpFile = "classicListDump1.html";
    const char* nameOfTextGraphFile = "classicGraphDump.txt";

    dumpInfo.nameOfDumpFile = nameOfDumpFile;
    dumpInfo.nameOfGraphFile = nameOfTextGraphFile;


    listNode_t* nullNode = classicListCtor(&cList);


    listNode_t* node1 = ClassicInsertAfter(&cList, nullNode, 10, &dumpInfo);

    listNode_t* node2 = ClassicInsertAfter(&cList, node1, 20, &dumpInfo);

    listNode_t* node3 = ClassicInsertAfter(&cList, node2, 30, &dumpInfo);

    listNode_t* node4 = ClassicInsertAfter(&cList, node3, 40, &dumpInfo);

    listNode_t* node5 = ClassicInsertAfter(&cList, node4, 50, &dumpInfo);

    node4->next = node2;
    node2->next = node1;
    //node2->prev = node3;
    listNode_t* node6 = ClassicInsertAfter(&cList, node5, 60, &dumpInfo);

    ClassicInsertAfter(&cList, node6, 70, &dumpInfo);

    ClassicDeleteNode (&cList, node3, &dumpInfo);

    classicListDtor(nullNode);
*/

    return 0;
}
