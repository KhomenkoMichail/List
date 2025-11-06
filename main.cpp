#include <stdio.h>

#include "listFunctions.h"
#include "structsAndConsts.h"
#include "classicListFunctions.h"
#include "testFunctions.h"
#include <stdlib.h>
#include <TXLib.h>

int main (void) {


    struct list lst = {};
    struct info listInfo = {};
    struct dump dumpInfo1 = {};

    struct classicList cList = {};
    struct dump dumpInfo = {};

    double classicTime = 0;
    double hashFriendlyTime = 0;

    LIST_CTOR(lst, 3, listInfo);
    listNode_t* nullNode = classicListCtor(&cList);
    classicTime = classicListTimetest (&cList, &dumpInfo1);

    hashFriendlyTime = hashFriendlyListTimetest (&lst, &dumpInfo);
    printf("diff == %lf\n", classicTime / hashFriendlyTime);

    listDtor(&lst);
    classicListDtor(nullNode);


/*
    struct list lst = {};
    struct info listInfo = {};
    struct dump dumpInfo = {};

    const char* nameOfDumpFile = "listDump.html";
    const char* nameOfTextGraphFile = "graphDump.txt";

    dumpInfo.nameOfDumpFile = nameOfDumpFile;
    dumpInfo.nameOfGraphFile = nameOfTextGraphFile;

    LIST_CTOR(lst, 3, listInfo);

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

    if(!(*isListLinear(&lst)))
        MakeListLinear(&lst, &dumpInfo);

    listDtor(&lst);
*/
/*
    struct classicList cList = {};
    struct dump dumpInfo = {};

    const char* nameOfDumpFile = "classicListDump2.html";
    const char* nameOfTextGraphFile = "classicGraphDump.txt";

    dumpInfo.nameOfDumpFile = nameOfDumpFile;
    dumpInfo.nameOfGraphFile = nameOfTextGraphFile;


    listNode_t* nullNode = classicListCtor(&cList);
    if (!nullNode)
        return 1;

    listNode_t* node1 = ClassicInsertAfter(&cList, nullNode, 10, &dumpInfo);
    if (!node1)
        return 1;

    listNode_t* node2 = ClassicInsertAfter(&cList, node1, 20, &dumpInfo);
    if (!node2)
        return 1;
    listNode_t* node3 = ClassicInsertAfter(&cList, node2, 30, &dumpInfo);
    if (!node3)
        return 1;
    listNode_t* node4 = ClassicInsertAfter(&cList, node3, 40, &dumpInfo);
    if (!node4)
        return 1;
    listNode_t* node5 = ClassicInsertAfter(&cList, node4, 50, &dumpInfo);
    if (!node5)
        return 1;
    node4->prev = (listNode_t*)0x12345678;

    listNode_t* node6 = ClassicInsertAfter(&cList, node5, 60, &dumpInfo);

    if (!node6)
        return 1;

    ClassicInsertAfter(&cList, node6, 70, &dumpInfo);

    ClassicDeleteNode (&cList, node3, &dumpInfo);

    classicListDtor(nullNode);
*/

    return 0;
}
