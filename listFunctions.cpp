#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "listFunctions.h"
#include "structsAndConsts.h"

void listCtor (struct list* lst, ssize_t capacity, struct info listInfo) {
    assert(lst);

    lst->nodeArr = (struct node*)calloc(capacity, sizeof(struct node));
    lst->capacity = capacity;

    ((lst->nodeArr)[0]).data = nullData;
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

    lst->errorCode = noErrors;
}

int insortAfter (struct list* lst, size_t anchorElemNum, listData_t dataValue) {
    assert(lst);

    struct node* nodes = lst->nodeArr;

    if(lst->free == 0)
        reallocList(lst);
        //continue;   //realloc

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

int deleteElem (struct list* lst, size_t deletedElem) {
    assert(lst);

    struct node* nodes = lst->nodeArr;

    if(deletedElem == lst->head)
        lst->head = (nodes[deletedElem]).next;

    if(deletedElem == lst->tail)
        lst->tail = (nodes[deletedElem]).prev;

    (nodes[deletedElem]).data = POISON;

    size_t prevElemNum = (nodes[deletedElem]).prev;
    size_t nextElemNum = (nodes[deletedElem]).next;

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

/*int listVerifier (struct list* lst) {
    if (stackPtrIsNull (stack, stdout))
        return badStackPtr;

    if (stack->data == NULL)
        stack->errorCode |= badDataPtr;

    if ((stack->size < 0) || ((stack->size > stack->capacity) && (stack->capacity >= 0))  || (stack->size > MAX_CAPACITY))
        stack->errorCode |= badSize;

    if ((stack->capacity <= 0) || (stack->capacity > MAX_CAPACITY))
        stack->errorCode |= badCapacity;

    return stack->errorCode;
}*/

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
    fprintf(graphFile, "    rankdir=LR;\n");
    fprintf(graphFile, "    node [shape = Mrecord, color = black];\n\n");

    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++) {

        const char* fillColor = "#C2BBBD";

        if (numOfNode == lst->head)
            fillColor = "#79D47F";

        if (numOfNode == lst->tail)
            fillColor = "#E07397";

        if (((lst->nodeArr)[numOfNode]).prev == -1)
            fillColor = "#E3f194";

        fprintf(graphFile, "    node%d [rank = 2,label = \" idx: %d| data = %d|<f2> next = %d| prev = %d\", style = filled, fillcolor = \"%s\", color = black];\n",
                numOfNode, numOfNode, ((lst->nodeArr)[numOfNode]).data, ((lst->nodeArr)[numOfNode]).next, ((lst->nodeArr)[numOfNode]).prev, fillColor);
    }

    fprintf(graphFile, "\n");

    for (size_t numOfNode = 0; numOfNode < lst->capacity - 1; numOfNode++)
        fprintf(graphFile, "    node%d -> node%d [weight = 500, style = invis, color = white];\n", numOfNode, numOfNode + 1);

    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++) {

        if (((lst->nodeArr)[numOfNode]).prev == -1)
            continue;

        // Связь next (синяя стрелка)
        if (((lst->nodeArr)[numOfNode]).next != 0)
            fprintf(graphFile, "    node%d -> node%d [color = blue, label = \"next\"];\n", numOfNode, ((lst->nodeArr)[numOfNode]).next);

        // Связь prev (красная стрелка)
        if (((lst->nodeArr)[numOfNode]).prev != 0)
            fprintf(graphFile, "    node%d -> node%d [color=red, label = \"prev\", style=dashed];\n", numOfNode, ((lst->nodeArr)[numOfNode]).prev);
    }

    for (size_t numOfNode = lst->free; ((lst->nodeArr)[numOfNode]).next != 0; numOfNode = ((lst->nodeArr)[numOfNode]).next)
        fprintf(graphFile, "    node%d -> node%d [color=gray, label=\"free\"];\n", numOfNode, ((lst->nodeArr)[numOfNode]).next);

    fprintf(graphFile, "\n");

    fprintf(graphFile, "    head [rank = 1, shape = box3d, label=\"head\", style = filled, fillcolor = \"#79D47F\", color = black];\n");
    fprintf(graphFile, "    tail [rank = 1, shape = box3d, label=\"tail\", style = filled, fillcolor = \"#E07397\", color = black];\n");
    fprintf(graphFile, "    free [rank = 1, shape = box3d, label=\"free\", style = filled, fillcolor = \"#E3f194\", color = black];\n");

    fprintf(graphFile, "    head -> node%d [color=darkblue];\n", lst->head);
    fprintf(graphFile, "    tail -> node%d [color=darkgreen];\n", lst->tail);
    fprintf(graphFile, "    free -> node%d [color=black];\n", lst->free);
    fprintf(graphFile, "}\n");


    if (fclose(graphFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", textGraphFileName);
        perror("");
        return 1;
    }

    return 0;
}



int fprintfGraphDump2 (struct list* lst, const char* textGraphFileName) {
    assert(lst);
    assert(textGraphFileName);

    FILE* graphFile = fopen(textGraphFileName, "w");

    if (graphFile == NULL) {
        fprintf(stderr, "Error of opening file \"%s\"", textGraphFileName);
        perror("");
        return 1;
    }

    fprintf(graphFile, "digraph List {\n");
    fprintf(graphFile, "    rankdir=HR;\n");
    fprintf(graphFile, "    node [shape = polygon, color = black];\n\n");

    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++) {

        const char* fillColor = "#C2BBBD";

        if (numOfNode == lst->head)
            fillColor = "#79D47F";

        if (numOfNode == lst->tail)
            fillColor = "#E07397";

        if (((lst->nodeArr)[numOfNode]).prev == -1)
            fillColor = "#E3f194";

        fprintf(graphFile, "    node%d [label = \"{ idx: %d| data = %d|<f2> next = %d| prev = %d}\", style = filled, fillcolor = \"%s\", color = black];\n",
                numOfNode, numOfNode, ((lst->nodeArr)[numOfNode]).data, ((lst->nodeArr)[numOfNode]).next, ((lst->nodeArr)[numOfNode]).prev, fillColor);
    }

    fprintf(graphFile, "\n");

    for (size_t numOfNode = 0; numOfNode < lst->capacity - 1; numOfNode++)
        fprintf(graphFile, "    node%d -> node%d [weight = 500, style = invis, color = white];\n", numOfNode, numOfNode + 1);

    for (size_t numOfNode = 0; numOfNode < lst->capacity; numOfNode++) {

        if (((lst->nodeArr)[numOfNode]).prev == -1)
            continue;

        // Связь next (синяя стрелка)
        if (((lst->nodeArr)[numOfNode]).next != 0)
            fprintf(graphFile, "    node%d -> node%d [color = blue, label = \"next\"];\n", numOfNode, ((lst->nodeArr)[numOfNode]).next);

        // Связь prev (красная стрелка)
        if (((lst->nodeArr)[numOfNode]).prev != 0)
            fprintf(graphFile, "    node%d -> node%d [color=red, label = \"prev\", style=dashed];\n", numOfNode, ((lst->nodeArr)[numOfNode]).prev);
    }

    for (size_t numOfNode = lst->free; ((lst->nodeArr)[numOfNode]).next != 0; numOfNode = ((lst->nodeArr)[numOfNode]).next)
        fprintf(graphFile, "    node%d -> node%d [color=gray, label=\"free\"];\n", numOfNode, ((lst->nodeArr)[numOfNode]).next);

    fprintf(graphFile, "\n");

    fprintf(graphFile, "    head [shape = box3d, label=\"head\", style = filled, fillcolor = \"#79D47F\", color = black];\n");
    fprintf(graphFile, "    tail [shape = box3d, label=\"tail\", style = filled, fillcolor = \"#E07397\", color = black];\n");
    fprintf(graphFile, "    free [shape = box3d, label=\"free\", style = filled, fillcolor = \"#E3f194\", color = black];\n");

    fprintf(graphFile, "    head -> node%d [color=darkblue];\n", lst->head);
    fprintf(graphFile, "    tail -> node%d [color=darkgreen];\n", lst->tail);
    fprintf(graphFile, "    free -> node%d [color=black];\n", lst->free);
    fprintf(graphFile, "    { rank = same; head; tail; free; }\n    { rank = same; node0; node1; node2; node3; node4; node5; node6; node7; node8; node9; }\n");
    fprintf(graphFile, "}\n");


    if (fclose(graphFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", textGraphFileName);
        perror("");
        return 1;
    }

    return 0;
}







