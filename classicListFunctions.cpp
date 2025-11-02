#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "structsAndConsts.h"
#include "listAccessFunctions.h"
#include "classicListFunctions.h"
#include <TXLib.h>

listNode_t* newListNode (listData_t dataValue) {
    listNode_t* newNode = (listNode_t*)calloc(1, sizeof(listNode_t));

    *(nodeData(newNode)) = dataValue;
    *(nodePrev(newNode)) = NULL;
    *(nodeNext(newNode)) = NULL;

    return newNode;
}

listNode_t* classicInsertAfter (listNode_t* anchorNode, listData_t dataValue, struct dump* dumpInfo) {
    assert(anchorNode);

    dumpInfo->nameOfFunc = __func__;

    char beforeMessage[STR_SIZE] =  {};
    char afterMessage[STR_SIZE]= {};
    snprintf(beforeMessage, sizeof(beforeMessage), "BEFORE Insert \"%d\" after  [%p]", dataValue, anchorNode);
    snprintf(afterMessage, sizeof(afterMessage), "AFTER Insert \"%d\" after [%p]",  dataValue, anchorNode);
$$
    if(classicListVerifier(anchorNode, dumpInfo)) {
        classicListDump(dumpInfo, beforeMessage);
        return NULL;
    }
$$
    classicListDump(dumpInfo, beforeMessage);
$$

    listNode_t* newNode = newListNode(dataValue);

    *(nodePrev(newNode)) = anchorNode;
    *(nodeNext(newNode)) = *(nodeNext(anchorNode));

    *(nodeNext(anchorNode)) = newNode;

    listNode_t* nextNodeAfterNew = *(nodeNext(newNode));
    *(nodePrev(nextNodeAfterNew)) = newNode;

    if(classicListVerifier(anchorNode, dumpInfo)) {
        classicListDump(dumpInfo, afterMessage);
        return NULL;
    }

    classicListDump(dumpInfo, afterMessage);

    return newNode;
}

int classicDeleteNode (listNode_t* deletedNode, struct dump* dumpInfo) {
    assert(deletedNode);

    dumpInfo->nameOfFunc = __func__;
    char beforeMessage[STR_SIZE] =  {};
    char afterMessage[STR_SIZE]= {};
    snprintf(beforeMessage, sizeof(beforeMessage), "BEFORE delete element [%p]", deletedNode);
    snprintf(afterMessage, sizeof(afterMessage), "AFTER delete element  [%p]", deletedNode);

    if(classicListVerifier(deletedNode, dumpInfo)) {
        classicListDump(dumpInfo, beforeMessage);
        return dumpInfo->errorCode;
    }

    classicListDump(dumpInfo, beforeMessage);

    listNode_t* prevNode = *(nodePrev(deletedNode));
    listNode_t* nextNode = *(nodeNext(deletedNode));

    *(nodeNext(prevNode)) = nextNode;
    *(nodePrev(nextNode)) = prevNode;

    free(deletedNode);

    if(classicListVerifier(dumpInfo->fictitiousNode, dumpInfo)) {
        classicListDump(dumpInfo, afterMessage);
        return dumpInfo->errorCode;
    }

    classicListDump(dumpInfo, afterMessage);

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
$$
    FILE* graphFile = fopen(textGraphFileName, "w");

    if (graphFile == NULL) {
        fprintf(stderr, "Error of opening file \"%s\"", textGraphFileName);
        perror("");
        return 1;
    }

    fprintf(graphFile, "digraph classicList {\n");
    fprintf(graphFile, "    rankdir = LR;\n");
    fprintf(graphFile, "    node [shape = Mrecord, color = black];\n");

    listNode_t* badNode1 = NULL;
    listNode_t* badNode2 = NULL;
$$
    for (listNode_t* node = fictitiousNode; ; node = *(nodeNext(node))) {

        const char* fillColor = "#C2BBBD";

        if (*(nodePrev(node)) == fictitiousNode)
            fillColor = "#79D47F";

        if (*(nodeNext(node)) == fictitiousNode)
            fillColor = "#E07397";

        if (*(nodeData(node)) == NULL_CANARY) {
            fprintf(graphFile, "    node%p [label = \" address = %p| data = CANARY|    next = %p| prev = %p\", style = filled, fillcolor = \"#dec84cff\", color = black];\n",
                node, node, *(nodeNext(node)), *(nodePrev(node)));

            if ((*(nodeNext(node)) == fictitiousNode))
                break;
            continue;
        }


        listNode_t* nextNum = *(nodeNext(node));
        if (nextNum == NULL)
            continue;
        if(node != *(nodePrev(nextNum))) {
            badNode1 = nextNum;
            //printf("yes\n");
            //break;
        }
        listNode_t* prevNum = *(nodePrev(node));
        if (nextNum == NULL)
            continue;
        if(node != *(nodeNext(prevNum)))
            badNode2 = prevNum;

        fprintf(graphFile, "    node%p [label = \" address = %p| data = %d|    next = %p| prev = %p\", style = filled, fillcolor = \"%s\", color = black];\n",
                node, node, *(nodeData(node)), *(nodeNext(node)), *(nodePrev(node)), fillColor);

        if ((*(nodeNext(node)) == fictitiousNode))
            break;

        if (nodeNext(node) == NULL)
            break;
        if ((node == badNode1) || (node == badNode2)) {
        //printf("yes\n");
        for (listNode_t* node1 = fictitiousNode; ; node1 = *(nodePrev(node1))) {
        const char* fillColor = "#C2BBBD";

        fprintf(graphFile, "    node%p [label = \" address = %p| data = %d|    next = %p| prev = %p\", style = filled, fillcolor = \"%s\", color = black];\n",
                node1, node1, *(nodeData(node1)), *(nodeNext(node1)), *(nodePrev(node1)), fillColor);

        if ((*(nodePrev(node1)) == fictitiousNode))
            break;
        if (nodePrev(node1) == NULL)
            break;
        if (((node1) == badNode1) || ((node1) == badNode2))
            break;
        }
            break;
        }

    }
$$
    fprintf(graphFile, "\n");
$$
    for (listNode_t* node = fictitiousNode; ; node = *(nodeNext(node))) {
        fprintf(graphFile, "    node%p -> node%p [weight = 500, style = invis, color = white];\n", node, *(nodeNext(node)));
        listNode_t* nextNum = *(nodeNext(node));
        if (nextNum == NULL)
            continue;
        if(node != *(nodePrev(nextNum)))
            break;
        listNode_t* prevNum = *(nodePrev(node));
        if (nextNum == NULL)
            continue;
        if(node != *(nodeNext(prevNum)))
            badNode2 = prevNum;

        if ((*(nodeNext(node)) == fictitiousNode))
            break;

        if ((node == badNode1) || (node == badNode2))
            break;
    }
$$
    for (listNode_t* node = fictitiousNode; ; node = *(nodeNext(node))) {

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
        if (nextNum == NULL)
            continue;
        if(node != *(nodePrev(nextNum)))
            break;
        listNode_t* prevNum = *(nodePrev(node));
        if (nextNum == NULL)
            continue;
        if(node != *(nodeNext(prevNum)))
            badNode2 = prevNum;

        if ((*(nodeNext(node)) == fictitiousNode))
            break;

        if ((node == badNode1) || (node == badNode2))
            break;
    }

    fprintf(graphFile, " }\n");
    fclose(graphFile);//FIXME
    return 0;
}

void classicListDtor (listNode_t* fictitiousNode) {
    assert(fictitiousNode);

    for(listNode_t* node = fictitiousNode; ; ) {
        listNode_t* nextNode = *(nodeNext(node));

        free(node);

        if(nextNode == fictitiousNode)
            break;
        node = nextNode;
    }
}

int classicListVerifier (listNode_t* node, struct dump* dumpInfo) {
    assert(node);
    assert(dumpInfo);

    if (noNextAndPrevMatch(node))
        dumpInfo->errorCode |= -badNextAndPrevMatch;

    if (classicListNodeCycle(node))
        dumpInfo->errorCode |= -badNodeCycle;

    return dumpInfo->errorCode;
}

int noNextAndPrevMatch (listNode_t* startNode) {
    assert(startNode);

    for (listNode_t* currentNode = startNode; ; ) {
        if (nodeNext(currentNode) == NULL)
            return 1;

        listNode_t* nextNode = *(nodeNext(currentNode));

        if(nodePrev(nextNode) == NULL)
            return 1;

        if (currentNode != *(nodePrev(nextNode)))
            return 1;

        currentNode = nextNode;

        if (currentNode == startNode)
            break;
    }

    return 0;
}

listErr_t classicListNodeCycle (listNode_t* startNode) {
    assert(startNode);

    size_t cycleCounter = 0;

    for (listNode_t* node = startNode; cycleCounter < MAX_CAPACITY; ) {
        if (nodeNext(node) == NULL)
            return badNodeCycle;

        if (*(nodeNext(node)) == startNode)
            break;
        cycleCounter++;
        node = *(nodeNext(node));
    }

    if(cycleCounter == MAX_CAPACITY)
        return badNodeCycle;

    cycleCounter = 0;

    for (listNode_t* node = startNode; cycleCounter < MAX_CAPACITY; ) {
        if (nodePrev(node) == NULL)
            return badNodeCycle;

        if (*(nodePrev(node)) == startNode)
            break;
        cycleCounter++;
        node = *(nodePrev(node));
    }

    if(cycleCounter == MAX_CAPACITY)
        return badNodeCycle;

    return noErrors;
}

void classicListDump (struct dump* dumpInfo, const char* message) {
    assert(dumpInfo);
    assert(message);

    const char* nameOfTextGraphFile = dumpInfo->nameOfGraphFile;
$$
    FILE* dumpFile = 0;
    if(dumpInfo->dumpFileWasOpened)
        dumpFile = fopen(dumpInfo->nameOfDumpFile, "a");
    else {
        dumpFile = fopen(dumpInfo->nameOfDumpFile, "w");
        dumpInfo->dumpFileWasOpened = 1;
    }
$$
    if (dumpFile == NULL) {
        fprintf(stderr, "Error of opening file \"%s\"", dumpInfo->nameOfDumpFile);
        perror("");
        return;
    }
$$
    fprintf(dumpFile, "<pre>\n");
    fprintf(dumpFile, "<h3>listDump() <font color=red>from %s at %s:%d</font></h3>\n",
    dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
$$
    fprintf(dumpFile, "<h2><font color=blue>%s</font></h2>\n", message);
$$
    fprintfClassicListErrorsForDump (dumpFile, dumpInfo);

if (!(dumpInfo->errorCode & -badNodeCycle) && !(dumpInfo->errorCode & -badNextAndPrevMatch))
    fprintfClassicListDataForDump (dumpInfo, dumpFile);

    createClassicListGraphImageForDump (dumpInfo, dumpFile, nameOfTextGraphFile);
$$
    if (fclose(dumpFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", dumpInfo->nameOfGraphFile);
        perror("");
        return;
    }
}

void fprintfClassicListDataForDump (struct dump* dumpInfo, FILE* dumpFile) {
    assert(dumpInfo);
    assert(dumpFile);

    fprintf(dumpFile, "errorCode == %d\n\n", dumpInfo->errorCode);

    fprintf(dumpFile, "address:  ");
    for (listNode_t* node = dumpInfo->fictitiousNode; (node != NULL) && (*(nodeNext(node)) != dumpInfo->fictitiousNode); node = *(nodeNext(node))) {
        fprintf(dumpFile, "[ %9p ]", node);

        if(nodeNext(node) == NULL)
            break;
    }
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "data:     ");
    for (listNode_t* node = dumpInfo->fictitiousNode; (node != NULL) && (*(nodeNext(node)) != dumpInfo->fictitiousNode); node = *(nodeNext(node))) {
        if(nodeData(node) == NULL)
            break;
        fprintf(dumpFile, "[ %9d ]", *(nodeData(node)));

        if(nodeNext(node) == NULL)
            break;
    }
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "next:     ");
    for (listNode_t* node = dumpInfo->fictitiousNode; (node != NULL) && (*(nodeNext(node)) != dumpInfo->fictitiousNode); node = *(nodeNext(node))) {
        if(nodeNext(node) == NULL)
            break;
        fprintf(dumpFile, "[ %9p ]", *(nodeNext(node)));

        if(nodeNext(node) == NULL)
            break;
    }
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "prev:     ");
     for (listNode_t* node = dumpInfo->fictitiousNode; (node != NULL) && (*(nodeNext(node)) != dumpInfo->fictitiousNode); node = *(nodeNext(node))) {
        if(nodePrev(node) == NULL)
            break;
        fprintf(dumpFile, "[ %9p ]", *(nodePrev(node)));

        if(nodeNext(node) == NULL)
            break;
    }
    fprintf(dumpFile, "\n");
}

void createClassicListGraphImageForDump (struct dump* dumpInfo, FILE* dumpFile, const char* nameOfTextGraphFile) {
    assert(dumpInfo);
    assert(dumpFile);
    assert(nameOfTextGraphFile);
$$
    static int graphImageCounter = 0;
    graphImageCounter++;
$$
    printf("fictitiousNode == %p\n", dumpInfo->fictitiousNode);
    classicListGraphDump (dumpInfo->fictitiousNode, nameOfTextGraphFile);
$$
    char graphvizCallCommand[STR_SIZE] = {};
    printf("nameOfTextGraphFile == %s\n", nameOfTextGraphFile);
    snprintf(graphvizCallCommand, sizeof(graphvizCallCommand), "dot -Tpng %s -o GRAPH_DUMPS/graph%d.png", nameOfTextGraphFile, graphImageCounter);
    system(graphvizCallCommand);
    fprintf(dumpFile, "Image:\n <img src=GRAPH_DUMPS/graph%d.png width=1000>\n", graphImageCounter);
}

void fprintfClassicListErrorsForDump (FILE* dumpFile, struct dump* dumpInfo) {
    assert(dumpFile);
    assert(dumpInfo);

    if (dumpInfo->errorCode & -badNodeCycle) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! BAD NODE CYCLE! errorcode = %d</font></h2>\n", badNodeCycle);
        printf("ERROR! BAD NODE CYCLE! errorcode = %d; In func %s from %s:%d\n",
        badNodeCycle, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (dumpInfo->errorCode & -badNextAndPrevMatch) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! NEXT VALUES DO NOT MATCH WITH PREV! errorcode = %d</font></h2>\n",
        badNextAndPrevMatch);
        printf("ERROR! NEXT VALUES DO NOT MATCH WITH PREV! errorcode = %d; In func %s from %s:%d\n",
        badNextAndPrevMatch, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }
}
