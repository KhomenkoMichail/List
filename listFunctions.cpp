#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "listFunctions.h"
#include "structsAndConsts.h"


void listCtor (struct list* lst, ssize_t capacity, struct info listInfo, struct dump* dumpInfo) {
    assert(lst);

    lst->nodeArr = (struct node*)calloc(capacity, sizeof(struct node));
    lst->capacity = capacity;

    ((lst->nodeArr)[0]).data = NULL_CANARY;
    ((lst->nodeArr)[0]).next = 0;
    ((lst->nodeArr)[0]).prev = 0;

    for (int nodeNum = 1; nodeNum < capacity; nodeNum++) {
        ((lst->nodeArr)[nodeNum]).data = 0xBAD;
        ((lst->nodeArr)[nodeNum]).next = nodeNum + 1;
        ((lst->nodeArr)[nodeNum]).prev = -1;
    }

    ((lst->nodeArr)[capacity - 1]).next = 0;

    lst->head = 0;
    lst->tail = 0;
    lst->free = 1;

    (lst->creationInfo).name = listInfo.name;
    (lst->creationInfo).nameOfFunc = listInfo.nameOfFunc;
    (lst->creationInfo).nameOfFile = listInfo.nameOfFile;
    (lst->creationInfo).numOfLine = listInfo.numOfLine;

    FILE* dumpFile = fopen(dumpInfo->nameOfHTMLFile, "w");
    if (dumpFile == NULL) {
        fprintf(stderr, "Error of opening file \"%s\"", dumpInfo->nameOfHTMLFile);
        perror("");
        return;
    }

    fprintf(dumpFile, "<pre>\n");

    /*if (fclose(dumpFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", dumpInfo.nameOfHTMLFile);
        perror("");
        return;
    }*/
    dumpInfo->HTMLFilePtr = dumpFile;

    lst->errorCode = noErrors;
}

int insortAfter (struct list* lst, size_t anchorElemNum, listData_t dataValue) {
    assert(lst);

    struct node* nodes = lst->nodeArr;

    if(lst->free == 0)
        reallocList(lst);

    size_t freeNum = lst->free;

    if(anchorElemNum == lst->tail)
        lst->tail = freeNum;

    if((anchorElemNum < lst->head) || (lst->head == 0))
        lst->head = freeNum;

    (nodes[freeNum]).data = dataValue;
    (nodes[freeNum]).prev = anchorElemNum;

    size_t nextFreeNum = (nodes[freeNum]).next;

    (nodes[freeNum]).next = (nodes[anchorElemNum]).next;

    if(anchorElemNum != 0)
        (nodes[anchorElemNum]).next = freeNum;

    size_t nextNumAfterNew = (nodes[freeNum]).next;

    if(nextNumAfterNew != 0)
        (nodes[nextNumAfterNew]).prev = freeNum;

    lst->free = nextFreeNum;

    return 0;
}

int deleteElement (struct list* lst, size_t deletedElem) {
    assert(lst);

    struct node* nodes = lst->nodeArr;

    if(deletedElem == lst->head)
        lst->head = (nodes[deletedElem]).next;

    if(deletedElem == lst->tail)
        lst->tail = (nodes[deletedElem]).prev;

    (nodes[deletedElem]).data = POISON;

    int prevElemNum = (nodes[deletedElem]).prev;
    int nextElemNum = (nodes[deletedElem]).next;

    if(prevElemNum != 0)
        (nodes[prevElemNum]).next = (nodes[deletedElem]).next;

    (nodes[deletedElem]).next = lst->free;
    lst->free = deletedElem;

    if (nextElemNum != 0)
        (nodes[nextElemNum]).prev = prevElemNum;
    (nodes[deletedElem]).prev = -1;

    return 0;
}

int reallocList (struct list* lst) {
    assert(lst);

    lst->capacity *= 2;

    realloc(lst->nodeArr, (lst->capacity)*sizeof(struct node));

    for (size_t nodeNum = lst->capacity / 2; nodeNum < lst->capacity; nodeNum++) {
        ((lst->nodeArr)[nodeNum]).data = 0xBAD;
        ((lst->nodeArr)[nodeNum]).next = nodeNum + 1;
        ((lst->nodeArr)[nodeNum]).prev = -1;
    }

    ((lst->nodeArr)[lst->capacity - 1]).next = 0;

    lst->free = lst->capacity / 2;

    return 0;
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
    fprintf(graphFile, "    splines = ortho;");

    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++) {

        const char* fillColor = "#C2BBBD";

        if (numOfNode == lst->head)
            fillColor = "#79D47F";

        if (numOfNode == lst->tail)
            fillColor = "#E07397";

        if (((lst->nodeArr)[numOfNode]).prev == -1)
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

    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++) {

        if (((lst->nodeArr)[numOfNode]).prev == -1)
            continue;

       if (((lst->nodeArr)[numOfNode]).next != 0)
            fprintf(graphFile, "    node%d -> node%d [color = \"#83dd94\"];\n", numOfNode, ((lst->nodeArr)[numOfNode]).next);

        if (((lst->nodeArr)[numOfNode]).prev != 0)
            fprintf(graphFile, "    node%d -> node%d [color = \"#dd83cc\"];\n", numOfNode, ((lst->nodeArr)[numOfNode]).prev);
    }

    for (size_t numOfNode = lst->free; ((lst->nodeArr)[numOfNode]).next != 0; numOfNode = ((lst->nodeArr)[numOfNode]).next)
        fprintf(graphFile, "    node%d -> node%d [color = gray];\n", numOfNode, ((lst->nodeArr)[numOfNode]).next);

    fprintf(graphFile, "\n");

    fprintf(graphFile, "    head [shape = box3d, label=\"HEAD\", style = filled, fillcolor = \"#79D47F\", color = black];\n");
    fprintf(graphFile, "    tail [shape = box3d, label=\"TAIL\", style = filled, fillcolor = \"#E07397\", color = black];\n");
    fprintf(graphFile, "    free [shape = box3d, label=\"FREE\", style = filled, fillcolor = \"#E3f194\", color = black];\n");

    fprintf(graphFile, "    head -> node%d [color = \"#79D47F\"];\n", lst->head);
    fprintf(graphFile, "    tail -> node%d [color = \"#E07397\"];\n", lst->tail);
    fprintf(graphFile, "    free -> node%d [color = gray];\n", lst->free);

    fprintf(graphFile, "    { rank = same; head; tail; free; }\n");
    //for (size_t NumOfNode = 0; NumOfNode < lst->capacity; NumOfNode++)
    //    fprintf(graphFile, "node%d;", NumOfNode);

    fprintf(graphFile, " }\n");


    if (fclose(graphFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", textGraphFileName);
        perror("");
        return 1;
    }

    return 0;
}

void listDump (struct list* lst, struct dump* dumpInfo) {
    assert(lst);
    FILE* dumpFile = dumpInfo->HTMLFilePtr;
    //FILE* dumpFile = fopen(dumpInfo->nameOfHTMLFile, "a");

    /*if (dumpFile == NULL) {
        fprintf(stderr, "Error of opening file \"%s\"", dumpInfo->nameOfHTMLFile);
        perror("");
        return;
    }
    printf("succsess\n");*/

    //fprintf(dumpFile, "<pre>\n");
    fprintf(dumpFile, "<h3>listDump() <font color=red>from %s at %s:%d</font></h3>\n", dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    fprintf(dumpFile, "list \"%s\" [%p] from %s at %s:%d\n\n", (lst->creationInfo).name, lst, lst->creationInfo.nameOfFunc, lst->creationInfo.nameOfFile, lst->creationInfo.numOfLine);

    fprintfListErrorsForDump (lst, dumpFile);

    fprintfListDataForDump (lst, dumpFile);

    createGraphImageForDump (lst, dumpFile, dumpInfo->nameOfTextGraphFile);

    /*if (fclose(dumpFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", dumpInfo->nameOfTextGraphFile);
        perror("");
        return;
    }*/
}

void fprintfListDataForDump (struct list* lst, FILE* dumpFile) {
    assert(lst);
    assert(dumpFile);

    fprintf(dumpFile, "capacity == %d\n", lst->capacity);
    fprintf(dumpFile, "errorCode == %d\n\n", lst->errorCode);

    fprintf(dumpFile, "head == %d\n", lst->head);
    fprintf(dumpFile, "tail == %d\n", lst->tail);
    fprintf(dumpFile, "free == %d\n\n", lst->free);

    fprintf(dumpFile, "idx: ");
    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++)
        fprintf(dumpFile, "%5d", numOfNode);
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "data: ");
    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++)
        fprintf(dumpFile, "%5d", ((lst->nodeArr)[numOfNode]).data);
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "next: ");
    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++)
        fprintf(dumpFile, "%5d", ((lst->nodeArr)[numOfNode]).next);
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "prev: ");
    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++)
        fprintf(dumpFile, "%5d", ((lst->nodeArr)[numOfNode]).prev);
    fprintf(dumpFile, "\n");
}

void createGraphImageForDump (struct list* lst, FILE* dumpFile, const char* nameOfTextGraphFile) {
    assert(lst);
    assert(dumpFile);
    assert(nameOfTextGraphFile);

    static int graphImageCounter = 0;
    graphImageCounter++;

    fprintfGraphDump (lst, nameOfTextGraphFile);

    char graphvizCallCommand[64] = {};
    snprintf(graphvizCallCommand, sizeof(graphvizCallCommand), "dot -Tpng %s -o graph%d.png", nameOfTextGraphFile, graphImageCounter);
    system(graphvizCallCommand);
    fprintf(dumpFile, "Image:\n <img src=graph%d.png width=200px>\n", graphImageCounter);
}

int listVerifier (struct list* lst) {
    if (!lst)
        return badListPtr;

    if (lst->nodeArr == NULL)
        lst->errorCode |= badNodeArrPtr;

    if (lst->capacity > MAX_CAPACITY)
        lst->errorCode |= badCapacity;

    if ((((lst->nodeArr)[0]).data != NULL_CANARY) || (((lst->nodeArr)[0]).next != 0) || (((lst->nodeArr)[0]).prev != 0))
        lst->errorCode |= badNullNode;

    if (((lst->nodeArr)[lst->head]).prev != 0)
        lst->errorCode |= badHead;

    if (((lst->nodeArr)[lst->tail]).next != 0)
        lst->errorCode |= badTail;

    if (findBadFreeNode(lst))
        lst->errorCode |= badFreeNode;

    if (findBadNextAndPrevMatch(lst))
        lst->errorCode |= badNextAndPrevMatch;

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

    for (int numOfNode = 1; numOfNode < (int)lst->capacity; numOfNode++) {
        if((numOfNode == (int)lst->tail) || (((lst->nodeArr)[numOfNode])).data == POISON)
            continue;

        int nextNum = (((lst->nodeArr)[numOfNode])).next;
        struct node nextNode = (lst->nodeArr)[nextNum];
        if (numOfNode != nextNode.prev)
            return 1;
    }

    return 0;
}

void fprintfListErrorsForDump (struct list* lst, FILE* dumpFile) {
    assert(lst);
    assert(dumpFile);

    if (lst->errorCode & badNodeArrPtr)
        fprintf(dumpFile, "<h2><font color=red>ERROR! NODE ARRAY POINTER IS NULL! errorcode = %d</font></h2>\n", badNodeArrPtr);

    if (lst->errorCode & badCapacity)
        fprintf(dumpFile, "<h2><font color=red>ERROR! CAPACITY IS TOO BIG! errorcode = %d</font></h2>\n", badCapacity);

    if (lst->errorCode & badNullNode)
        fprintf(dumpFile, "<h2><font color=red>ERROR! NULL NODE VALUES WERE DAMAGED! errorcode = %d</font></h2>\n", badNullNode);

    if (lst->errorCode & badFreeNode)
        fprintf(dumpFile, "<h2><font color=red>ERROR! FREE NODE(S) VALUES WERE DAMAGED! errorcode = %d</font></h2>\n", badFreeNode);

    if (lst->errorCode & badNextAndPrevMatch)
        fprintf(dumpFile, "<h2><font color=red>ERROR! NEXT VALUES DO NOT MATCH WITH PREV! errorcode = %d</font></h2>\n", badNextAndPrevMatch);

    if (lst->errorCode & badHead)
        fprintf(dumpFile, "<h2><font color=red>ERROR! BAD HEAD VALUE! errorcode = %d</font></h2>\n", badHead);

    if (lst->errorCode & badTail)
        fprintf(dumpFile, "<h2><font color=red>ERROR! BAD TAIL VALUE! errorcode = %d</font></h2>\n", badTail);
}
