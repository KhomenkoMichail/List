#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "structsAndConsts.h"
#include "listAccessFunctions.h"
#include "classicListFunctions.h"

listNode_t* newListNode (listData_t dataValue) {
    listNode_t* newNode = (listNode_t*)calloc(1, sizeof(listNode_t));

    *(nodeData(newNode)) = dataValue;
    *(nodePrev(newNode)) = NULL;
    *(nodeNext(newNode)) = NULL;

    return newNode;
}

listNode_t* classicInsertAfter (listNode_t* anchorNode, listData_t dataValue) {
    assert(anchorNode);

    listNode_t* newNode = newListNode(dataValue);
    *(nodePrev(newNode)) = anchorNode;
    *(nodeNext(newNode)) = *(nodeNext(anchorNode));

    *(nodeNext(anchorNode)) = newNode;

    return newNode;
}

int classicDeleteNode (listNode_t* deletedNode) {
    assert(deletedNode);

    listNode_t* prevNode = *(nodePrev(deletedNode));
    listNode_t* nextNode = *(nodeNext(deletedNode));

    *(nodeNext(prevNode)) = nextNode;
    *(nodePrev(nextNode)) = prevNode;

    free(deletedNode);
    return 0;
}

listNode_t* classicListCtor(void){
    listNode_t* fictitiousNode = newListNode (NULL_CANARY);

    *(nodePrev(fictitiousNode)) = fictitiousNode;
    *(nodeNext(fictitiousNode)) = fictitiousNode;

    return fictitiousNode;
}

int classicListGraphDump (listNode_t* fictitiousNode, const char* textGraphFileName) {
    assert(fictitiousNode);

    FILE* graphFile = fopen(textGraphFileName, "w");

    if (graphFile == NULL) {
        fprintf(stderr, "Error of opening file \"%s\"", textGraphFileName);
        perror("");
        return 1;
    }

    fprintf(graphFile, "digraph classicList {\n");
    fprintf(graphFile, "    rankdir = LR;\n");
    fprintf(graphFile, "    node [shape = Mrecord, color = black];\n");

    for (listNode_t* node = fictitiousNode; node != NULL ; node = *(nodeNext(node))) {

        const char* fillColor = "#C2BBBD";

        if (*(nodePrev(node)) == fictitiousNode)
            fillColor = "#79D47F";

        if (*(nodeNext(node)) == fictitiousNode)
            fillColor = "#E07397";

        fprintf(graphFile, "    node%p [label = \" address = %p| data = %d|    next = %p| prev = %p\", style = filled, fillcolor = \"%s\", color = black];\n",
                node, node, *(nodeData(node)), *(nodeNext(node)), *(nodePrev(node)), fillColor);
    }

    fprintf(graphFile, "\n");

    for (listNode_t* node = fictitiousNode; node != NULL; node = *(nodeNext(node))) {
        if ((*(nodeNext(node)) == NULL))
            break;
        fprintf(graphFile, "    node%p -> node%p [weight = 500, style = invis, color = white];\n", node, *(nodeNext(node)));
    }

    for (listNode_t* node = fictitiousNode; node != NULL ; node = *(nodeNext(node))) {

        listNode_t* nextNum = *(nodeNext(node));

        if (nextNum == NULL)
            continue;

        if(node == *(nodePrev(nextNum)))
            fprintf(graphFile, "    node%p -> node%p [dir = both, color = \"#9faafaff\"];\n", node, nextNum);
        else {
            fprintf(graphFile, "    node%p -> node%p [color = \"#220ff5ff\"];\n", node, nextNum);
            fprintf(graphFile, "    errorNode%p [shape = doubleoctagon, style = filled, fillcolor = \"#ff0000ff\",  color = \"#ff0000ff\", label = \" address = %p\", fontcolor = white];\n", *(nodePrev(nextNum)), *(nodePrev(nextNum)));
            fprintf(graphFile, "    node%p -> errorNode%p [color = \"#ff0000ff\", penwidth = 4];\n", nextNum, *(nodePrev(nextNum)));
        }
    }

    fprintf(graphFile, " }\n");
    return 0;
}

