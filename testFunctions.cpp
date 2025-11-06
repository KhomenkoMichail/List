#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <TXLib.h>

#include "testFunctions.h"
#include "listFunctions.h"
#include "classicListFunctions.h"


double classicListTimetest (struct classicList* cList, struct dump* dumpInfo) {
    assert(cList);
    assert(dumpInfo);

    LARGE_INTEGER startTestTime = {};
    LARGE_INTEGER endTestTime = {};

    //double testTime = 0;

    listNode_t* fictitiousNode = *cListFictitious(cList);
    listNode_t* newNode = NULL;

    QueryPerformanceCounter(&startTestTime);

    for (size_t numOfTheTest = 0; numOfTheTest < NUMBER_OF_TESTS; numOfTheTest++) {
        newNode = classicInsertAfter (cList, fictitiousNode, 10, dumpInfo);
        classicDeleteNode (cList, newNode, dumpInfo);
    }

    QueryPerformanceCounter(&endTestTime);


    printf("Time of the classic list test == %lf\n", (double)(endTestTime.QuadPart - startTestTime.QuadPart));
    return (double)(endTestTime.QuadPart - startTestTime.QuadPart);
}

double hashFriendlyListTimetest (struct list* lst, struct dump* dumpInfo) {
    assert(lst);
    assert(dumpInfo);

    LARGE_INTEGER startTestTime = {};
    LARGE_INTEGER endTestTime = {};

    //double testTime = 0;

    //startTestTime = time(NULL);
    QueryPerformanceCounter(&startTestTime);

    for (size_t numOfTheTest = 0; numOfTheTest < NUMBER_OF_TESTS; numOfTheTest++) {
        insertAfter (lst, 0, 10, dumpInfo);
        deleteElement (lst, 1, dumpInfo);
    }

    //endTestTime = time(NULL);
    QueryPerformanceCounter(&endTestTime);

    //testTime = difftime(endTestTime, startTestTime);
    printf("Time of the hash friendly list test == %lf\n", (double)(endTestTime.QuadPart - startTestTime.QuadPart));
    return (double)(endTestTime.QuadPart - startTestTime.QuadPart);
}

