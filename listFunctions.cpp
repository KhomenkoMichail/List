#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "listFunctions.h"
#include "structsAndConsts.h"
#include "listAccessFunctions.h"
#include "TXLib.h"

int listCtor (struct list* lst, ssize_t capacity, struct info listInfo) {
    assert(lst);

    lst->nodeArr = (struct node*)calloc(capacity, sizeof(struct node));
    lst->capacity = capacity;
    lst->size = 0;

    ((lst->nodeArr)[0]).data = NULL_CANARY;
    ((lst->nodeArr)[0]).next = 0;
    ((lst->nodeArr)[0]).prev = 0;

    for (int nodeNum = 1; nodeNum < capacity; nodeNum++) {
        ((lst->nodeArr)[nodeNum]).data = 0xBAD;
        ((lst->nodeArr)[nodeNum]).next = nodeNum + 1;
        ((lst->nodeArr)[nodeNum]).prev = -1;
    }

    ((lst->nodeArr)[capacity - 1]).next = 0;

    lst->free = 1;

    (lst->creationInfo).name = listInfo.name;
    (lst->creationInfo).nameOfFunc = listInfo.nameOfFunc;
    (lst->creationInfo).nameOfFile = listInfo.nameOfFile;
    (lst->creationInfo).numOfLine = listInfo.numOfLine;

    lst->errorCode = noErrors;
    listVerifier(lst);

    return lst->errorCode;
}

int deleteElement (struct list* lst, size_t deletedElement, struct dump* dumpInfo) {
    assert(lst);

    dumpInfo->nameOfFunc = __func__;
    char beforeMessage[STR_SIZE] =  {};
    char afterMessage[STR_SIZE]= {};
    snprintf(beforeMessage, sizeof(beforeMessage), "BEFORE delete element with idx [%d]", deletedElement);
    snprintf(afterMessage, sizeof(afterMessage), "AFTER delete element with idx [%d]", deletedElement);

    if (findBadDeleteNum(lst, deletedElement, dumpInfo))
        return badDeleteNum;

    if(listVerifier(lst)) {
        listDump (lst, dumpInfo, beforeMessage);
        return lst->errorCode;
    }

    listDump (lst, dumpInfo, beforeMessage);

    *(listData(lst, deletedElement)) = POISON;

    int prevElemNum = *(listPrev(lst, deletedElement));
    int nextElemNum = *(listNext(lst, deletedElement));

    *(listNext(lst, prevElemNum)) = *(listNext(lst, deletedElement));
    *(listNext(lst, deletedElement)) = *(listFree(lst));

    *(listPrev(lst, nextElemNum)) = prevElemNum;
    *(listPrev(lst, deletedElement)) = -1;

    *(listFree(lst)) = deletedElement;
    *(listSize(lst)) -= 1;

    if(listVerifier(lst)) {
        listDump (lst, dumpInfo, beforeMessage);
        return lst->errorCode;
    }

    listDump (lst, dumpInfo, afterMessage);
    return 0;
}

listErr_t reallocList (struct list* lst) {
    assert(lst);

    lst->capacity *= 2;

    struct node* newArr = (struct node*)realloc(lst->nodeArr, (lst->capacity)*sizeof(struct node));
    if (!newArr) {
        printf("Error! Bad realloc!\n");
        return badRealloc;
    }
    lst->nodeArr = newArr;

    for (size_t nodeNum = lst->capacity / 2; nodeNum < lst->capacity; nodeNum++) {
        ((lst->nodeArr)[nodeNum]).data = 0xBAD;
        ((lst->nodeArr)[nodeNum]).next = nodeNum + 1;
        ((lst->nodeArr)[nodeNum]).prev = -1;
    }

    ((lst->nodeArr)[lst->capacity - 1]).next = 0;

    lst->free = lst->capacity / 2;
    return noErrors;
}

int fprintfGraphDump (struct list* lst, const char* textGraphFileName) {
    assert(lst);
    assert(textGraphFileName);

    FILE* graphFile = fopen(textGraphFileName, "w");

    if (graphFile == NULL) {
        fprintf(stderr, "Error of opening file \"%s\"", textGraphFileName);
        perror("");
        return 1;
    }

    fprintf(graphFile, "digraph List {\n");
    fprintf(graphFile, "    rankdir = LR;\n");
    fprintf(graphFile, "    node [shape = Mrecord, color = black];\n");
    //fprintf(graphFile, "    splines = ortho;");

    for (int numOfNode = 0; numOfNode < (int)(lst->capacity); numOfNode++) {

        const char* fillColor = "#C2BBBD";

        if (numOfNode == *(listHead(lst)))
            fillColor = "#79D47F";

        if (numOfNode == *(listTail(lst)))
            fillColor = "#E07397";

        if ((*(listData(lst, numOfNode)) == POISON) && (*(listPrev(lst, numOfNode)) == -1))
            fillColor = "#E3f194";

        switch (((lst->nodeArr)[numOfNode]).data) {
            case POISON:
                fprintf(graphFile, "    node%d [label = \" idx = %d| data = PZN|", numOfNode, numOfNode);
                break;
            case NULL_CANARY:
                fprintf(graphFile, "    node%d [label = \" idx = %d| data = CANARY|", numOfNode, numOfNode);
                break;
            default:
                fprintf(graphFile, "    node%d [label = \" idx = %d| data = %d|", numOfNode, numOfNode, ((lst->nodeArr)[numOfNode]).data);
                break;
        }

        fprintf(graphFile, "    next = %d| prev = %d\", style = filled, fillcolor = \"%s\", color = black];\n",
                ((lst->nodeArr)[numOfNode]).next, ((lst->nodeArr)[numOfNode]).prev, fillColor);
    }

    fprintf(graphFile, "\n");

    for (size_t numOfNode = 0; numOfNode < lst->capacity - 1; numOfNode++)
        fprintf(graphFile, "    node%d -> node%d [weight = 500, style = invis, color = white];\n", numOfNode, numOfNode + 1);

    for (int numOfNode = 0; numOfNode < (int)lst->capacity; numOfNode++) {

        if (*(listPrev(lst, numOfNode)) == -1)
            continue;

        size_t nextNum = *(listNext(lst, numOfNode));

        if (numOfNode == *(listPrev(lst, nextNum)))
            fprintf(graphFile, "    node%d -> node%d [dir = both, color = \"#9faafaff\"];\n", numOfNode, nextNum);
        else {
            fprintf(graphFile, "    node%d -> node%d [color = \"#220ff5ff\"];\n", numOfNode, *(listNext(lst, numOfNode)));
            fprintf(graphFile, "    errorNode%d [shape = doubleoctagon, style = filled, fillcolor = \"#ff0000ff\", color = \"#ff0000ff\", label = \" idx = %d\"];\n", *(listPrev(lst, nextNum)), *(listPrev(lst, nextNum)));
            fprintf(graphFile, "    node%d -> errorNode%d [color = \"#ff0000ff\"];\n", nextNum, *(listPrev(lst, nextNum)));
        }
    }

    for (size_t numOfNode = lst->free; (((lst->nodeArr)[numOfNode]).next != 0) && (lst->free != 0); numOfNode = ((lst->nodeArr)[numOfNode]).next)
        fprintf(graphFile, "    node%d -> node%d [color = gray];\n", numOfNode, ((lst->nodeArr)[numOfNode]).next);

    fprintf(graphFile, "\n");

    fprintf(graphFile, "    head [shape = box3d, label=\"HEAD\", style = filled, fillcolor = \"#79D47F\", color = black];\n");
    fprintf(graphFile, "    tail [shape = box3d, label=\"TAIL\", style = filled, fillcolor = \"#E07397\", color = black];\n");
    fprintf(graphFile, "    free [shape = box3d, label=\"FREE\", style = filled, fillcolor = \"#E3f194\", color = black];\n");

    fprintf(graphFile, "    head -> node%d [color = \"#79D47F\"];\n", *(listHead(lst)));
    fprintf(graphFile, "    tail -> node%d [color = \"#E07397\"];\n", *(listTail(lst)));
    if (*(listFree(lst)) != 0)
        fprintf(graphFile, "    free -> node%d [color = gray];\n", *(listFree(lst)));

    fprintf(graphFile, "    { rank = same; head; tail; free; }\n");

    fprintf(graphFile, " }\n");


    if (fclose(graphFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", textGraphFileName);
        perror("");
        return 1;
    }

    return 0;
}

void listDump (struct list* lst, struct dump* dumpInfo, const char* message) {
    assert(lst);
    assert(dumpInfo);
    assert(message);

    const char* nameOfTextGraphFile = dumpInfo->nameOfGraphFile;

    FILE* dumpFile = 0;
    if(dumpInfo->dumpFileWasOpened)
        dumpFile = fopen(dumpInfo->nameOfDumpFile, "a");
    else {
        dumpFile = fopen(dumpInfo->nameOfDumpFile, "w");
        dumpInfo->dumpFileWasOpened = 1;
    }

    if (dumpFile == NULL) {
        fprintf(stderr, "Error of opening file \"%s\"", dumpInfo->nameOfDumpFile);
        perror("");
        return;
    }

    fprintf(dumpFile, "<pre>\n");
    fprintf(dumpFile, "<h3>listDump() <font color=red>from %s at %s:%d</font></h3>\n", dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    fprintf(dumpFile, "<h2><font color=blue>%s</font></h2>\n", message);
    fprintf(dumpFile, "list \"%s\" [%p] from %s at %s:%d\n\n", (lst->creationInfo).name, lst, lst->creationInfo.nameOfFunc, lst->creationInfo.nameOfFile, lst->creationInfo.numOfLine);


    fprintfListErrorsForDump (lst, dumpFile, dumpInfo);

    if(!(lst->errorCode & badCapacity)) {
        fprintfListDataForDump (lst, dumpFile);
        createGraphImageForDump (lst, dumpFile, nameOfTextGraphFile);
    }

    if (fclose(dumpFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", dumpInfo->nameOfGraphFile);
        perror("");
        return;
    }
}

void fprintfListDataForDump (struct list* lst, FILE* dumpFile) {
    assert(lst);
    assert(dumpFile);

    fprintf(dumpFile, "capacity == %d\n", lst->capacity);
    fprintf(dumpFile, "errorCode == %d\n\n", lst->errorCode);

    fprintf(dumpFile, "free == %d\n\n", lst->free);

    fprintf(dumpFile, "idx:  ");
    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++)
        fprintf(dumpFile, "[ %5d ]", numOfNode);
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "data: ");
    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++)
        fprintf(dumpFile, "[ %5d ]", ((lst->nodeArr)[numOfNode]).data);
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "next: ");
    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++)
        fprintf(dumpFile, "[ %5d ]", ((lst->nodeArr)[numOfNode]).next);
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "prev: ");
    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++)
        fprintf(dumpFile, "[ %5d ]", ((lst->nodeArr)[numOfNode]).prev);
    fprintf(dumpFile, "\n");
}

void createGraphImageForDump (struct list* lst, FILE* dumpFile, const char* nameOfTextGraphFile) {
    assert(lst);
    assert(dumpFile);
    assert(nameOfTextGraphFile);

    static int graphImageCounter = 0;
    graphImageCounter++;

    fprintfGraphDump (lst, nameOfTextGraphFile);

    char graphvizCallCommand[STR_SIZE] = {};
    snprintf(graphvizCallCommand, sizeof(graphvizCallCommand), "dot -Tpng %s -o GRAPH_DUMPS/graph%d.png", nameOfTextGraphFile, graphImageCounter);
    system(graphvizCallCommand);
    fprintf(dumpFile, "Image:\n <img src=GRAPH_DUMPS/graph%d.png width=%dpx>\n", graphImageCounter, lst->capacity*150);
}

int listVerifier (struct list* lst) {

    if (!lst)
        return badListPtr;

    if (lst->nodeArr == NULL)
        lst->errorCode |= badNodeArrPtr;

    if (lst->capacity > MAX_CAPACITY) {
        lst->errorCode |= badCapacity;
        return badCapacity;
    }

    if (((lst->nodeArr)[0]).data != NULL_CANARY)
        lst->errorCode |= badNullNode;

    if (((lst->nodeArr)[*(listHead(lst))]).prev != 0)
        lst->errorCode |= badHead;

    if (((lst->nodeArr)[*(listTail(lst))]).next != 0)
        lst->errorCode |= badTail;

    if (findBadFreeNode(lst))
        lst->errorCode |= badFreeNode;

    if (findBadNextAndPrevMatch(lst))
        lst->errorCode |= badNextAndPrevMatch;

    if ((lst->size > lst->capacity) || (lst->size > MAX_CAPACITY))
        lst->errorCode |= badSize;

    if (findBadNodeCycle(lst))
        lst->errorCode |= badNodeCycle;

    return lst->errorCode;
}


int findBadFreeNode (struct list* lst) {
    assert(lst);

    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++)
        if ((((lst->nodeArr)[numOfNode]).data == POISON) && (((lst->nodeArr)[numOfNode]).prev != -1))
            return 1;

    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++)
        if ((((lst->nodeArr)[numOfNode]).data != POISON) && (((lst->nodeArr)[numOfNode]).prev == -1))
            return 1;

    return 0;
}

int findBadNextAndPrevMatch (struct list* lst) {
    assert(lst);

    for (int numOfNode = 0; numOfNode < (int)lst->capacity; numOfNode++) {
        if((((lst->nodeArr)[numOfNode])).data == POISON)
            continue;

        int nextNum = (((lst->nodeArr)[numOfNode])).next;
        struct node nextNode = (lst->nodeArr)[nextNum];
        if (numOfNode != nextNode.prev)
            return 1;
    }

    return 0;
}

void fprintfListErrorsForDump (struct list* lst, FILE* dumpFile, struct dump* dumpInfo) {
    assert(lst);
    assert(dumpInfo);
    assert(dumpFile);

    if (lst->errorCode & badNodeArrPtr) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! NODE ARRAY POINTER IS NULL! errorcode = %d</font></h2>\n", badNodeArrPtr);
        printf("ERROR! NODE ARRAY POINTER IS NULL! errorcode = %d; In func %s from %s:%d\n", badNodeArrPtr, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (lst->errorCode & badCapacity) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! CAPACITY IS TOO BIG! errorcode = %d</font></h2>\n", badCapacity);
        printf("ERROR! CAPACITY IS TOO BIG! errorcode = %d; In func %s from %s:%d\n", badCapacity, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (lst->errorCode & badNullNode) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! NULL NODE VALUES WERE DAMAGED! errorcode = %d</font></h2>\n", badNullNode);
        printf("ERROR! NULL NODE VALUES WERE DAMAGED! errorcode = %d; In func %s from %s:%d\n", badNullNode, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (lst->errorCode & badFreeNode) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! FREE NODE(S) VALUES WERE DAMAGED! errorcode = %d</font></h2>\n", badFreeNode);
        printf("ERROR! FREE NODE(S) VALUES WERE DAMAGED! errorcode = %d; In func %s from %s:%d\n", badFreeNode, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (lst->errorCode & badNextAndPrevMatch) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! NEXT VALUES DO NOT MATCH WITH PREV! errorcode = %d</font></h2>\n", badNextAndPrevMatch);
        printf("ERROR! NEXT VALUES DO NOT MATCH WITH PREV! errorcode = %d; In func %s from %s:%d\n", badNextAndPrevMatch, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (lst->errorCode & badHead) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! BAD HEAD VALUE! errorcode = %d</font></h2>\n", badHead);
        printf("ERROR! BAD HEAD VALUE! errorcode = %d; In func %s from %s:%d\n", badHead, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (lst->errorCode & badTail) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! BAD TAIL VALUE! errorcode = %d</font></h2>\n", badTail);
        printf("ERROR! BAD TAIL VALUE! errorcode = %d; In func %s from %s:%d\n", badTail, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (lst->errorCode & badSize) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! BAD LIST SIZE! errorcode = %d</font></h2>\n", badSize);
        printf("ERROR! BAD LIST SIZE! errorcode = %d; In func %s from %s:%d\n", badSize, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (lst->errorCode & badNodeCycle) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! BAD NODE CYCLE! errorcode = %d</font></h2>\n", badNodeCycle);
        printf("ERROR! BAD NODE CYCLE! errorcode = %d; In func %s from %s:%d\n", badNodeCycle, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }
}

int insertAfter (struct list* lst, size_t anchorElemNum, listData_t dataValue, struct dump* dumpInfo) {
    assert(lst);

    dumpInfo->nameOfFunc = __func__;

    if (findBadAnchorElemNum(lst, anchorElemNum, dumpInfo))
        return badInsertAnchorNum;

    char beforeMessage[STR_SIZE] =  {};
    char afterMessage[STR_SIZE]= {};
    snprintf(beforeMessage, sizeof(beforeMessage), "BEFORE Insert \"%d\" after idx [%d]", dataValue, anchorElemNum);
    snprintf(afterMessage, sizeof(afterMessage), "AFTER Insert \"%d\" after idx [%d]",  dataValue, anchorElemNum);

    if(listVerifier(lst)) {
        listDump (lst, dumpInfo, beforeMessage);
        return lst->errorCode;
    }

    listDump (lst, dumpInfo, beforeMessage);

    if(lst->free == 0)
        if (reallocList(lst))
            return badRealloc;

    size_t newNodeNum = *(listFree(lst));

    *(listData(lst, newNodeNum)) = dataValue;
    *(listPrev(lst, newNodeNum)) = anchorElemNum;

    size_t nextFreeNum = *(listNext(lst, newNodeNum));

    *(listNext(lst, newNodeNum)) = *(listNext(lst, anchorElemNum));
    *(listNext(lst, anchorElemNum)) = newNodeNum;

    size_t nextNumAfterNew = *(listNext(lst, newNodeNum));
    *(listPrev(lst, nextNumAfterNew)) = newNodeNum;

    *listFree(lst) = nextFreeNum;
    *(listSize(lst)) += 1;

    if(listVerifier(lst)) {
        listDump (lst, dumpInfo, beforeMessage);
        return lst->errorCode;
    }

    listDump (lst, dumpInfo, afterMessage);
    return newNodeNum;
}

listErr_t findBadNodeCycle (struct list* lst) {
    assert(lst);

    size_t cycleCounter = 0;

    for (size_t numOfNode = 0; cycleCounter < 2*(lst->capacity); numOfNode = ((lst->nodeArr)[numOfNode]).next) {
        if (numOfNode > lst->capacity)
            return badNodeCycle;

        if (((lst->nodeArr)[numOfNode]).next == 0)
            break;
        cycleCounter++;
    }

    if(cycleCounter != lst->size)
        return badNodeCycle;

    cycleCounter = 0;

    for (size_t numOfNode = 0; cycleCounter < 2*(lst->capacity); numOfNode = ((lst->nodeArr)[numOfNode]).prev) {
        if (numOfNode > lst->capacity)
            return badNodeCycle;

        if (((lst->nodeArr)[numOfNode]).prev == 0)
            break;
        cycleCounter++;
    }

    if(cycleCounter != lst->size)
        return badNodeCycle;

    return noErrors;
}

listErr_t findBadAnchorElemNum (struct list* lst, size_t anchorElemNum, struct dump* dumpInfo) {
    assert(lst);

    if ((anchorElemNum > *(listCapacity(lst))) || (*(listPrev(lst, anchorElemNum)) == -1)) {
        printf("Error! Bad number of Anchor Element in %s from %s:%d\n", dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
        return badInsertAnchorNum;
    }

    return noErrors;
}

listErr_t findBadDeleteNum(struct list* lst, size_t deletedElement, struct dump* dumpInfo) {
    assert(lst);
    assert(dumpInfo);

    if ((deletedElement > *(listCapacity(lst))) || (*(listPrev(lst, deletedElement)) == -1)) {
        printf("Error! Bad number of deleted element in %s from %s:%d\n", dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
        return badDeleteNum;
    }

    return noErrors;
}

int insertBefore (struct list* lst, size_t anchorElemNum, listData_t dataValue, struct dump* dumpInfo) {
    assert(lst);
    assert(dumpInfo);

    dumpInfo->nameOfFunc = __func__;

    if (findBadAnchorElemNum(lst, anchorElemNum, dumpInfo))
        return badInsertAnchorNum;

    char beforeMessage[STR_SIZE] =  {};
    char afterMessage[STR_SIZE]= {};
    snprintf(beforeMessage, sizeof(beforeMessage), "BEFORE Insert \"%d\" before idx [%d]", dataValue, anchorElemNum);
    snprintf(afterMessage, sizeof(afterMessage), "AFTER Insert \"%d\" before idx [%d]",  dataValue, anchorElemNum);

    if(listVerifier(lst)) {
        listDump (lst, dumpInfo, beforeMessage);
        return lst->errorCode;
    }

    listDump (lst, dumpInfo, beforeMessage);

    if(lst->free == 0)
        if (reallocList(lst))
            return badRealloc;

    size_t newNodeNum = *(listFree(lst));

    size_t nextFreeNum = *(listNext(lst, newNodeNum));

    *(listData(lst, newNodeNum)) = dataValue;
    *(listNext(lst, newNodeNum)) = anchorElemNum;

    *(listPrev(lst, newNodeNum)) = *(listPrev(lst, anchorElemNum));
    *(listPrev(lst, anchorElemNum)) = newNodeNum;

    size_t prevNumAfterNew = *(listPrev(lst, newNodeNum));//
    *(listNext(lst, prevNumAfterNew)) = newNodeNum;//

    *listFree(lst) = nextFreeNum;
    *(listSize(lst)) += 1;

    if(listVerifier(lst)) {
        listDump (lst, dumpInfo, beforeMessage);
        return lst->errorCode;
    }

    listDump (lst, dumpInfo, afterMessage);

    return newNodeNum;
}
