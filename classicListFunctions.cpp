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

listNode_t* classicInsertAfter (struct classicList* cList, listNode_t* anchorNode, listData_t dataValue, struct dump* dumpInfo) {
    assert(anchorNode);

    dumpInfo->nameOfFunc = __func__;

    char beforeMessage[STR_SIZE] =  {};
    char afterMessage[STR_SIZE]= {};
    snprintf(beforeMessage, sizeof(beforeMessage), "BEFORE Insert \"%d\" after  [%p]", dataValue, anchorNode);
    snprintf(afterMessage, sizeof(afterMessage), "AFTER Insert \"%d\" after [%p]",  dataValue, anchorNode);
$$
    if(classicListVerifier(cList, dumpInfo)) {
        classicListDump(cList, dumpInfo, beforeMessage);
        return NULL;
    }
$$
    classicListDump(cList, dumpInfo, beforeMessage);
$$

    listNode_t* newNode = newListNode(dataValue);

    *(nodePrev(newNode)) = anchorNode;
    *(nodeNext(newNode)) = *(nodeNext(anchorNode));

    *(nodeNext(anchorNode)) = newNode;

    listNode_t* nextNodeAfterNew = *(nodeNext(newNode));
    *(nodePrev(nextNodeAfterNew)) = newNode;

    *cListSize(cList) += 1;

    if(classicListVerifier(cList, dumpInfo)) {
        classicListDump(cList, dumpInfo, afterMessage);
        return NULL;
    }

    classicListDump(cList, dumpInfo, afterMessage);

    return newNode;
}

int classicDeleteNode (struct classicList* cList, listNode_t* deletedNode, struct dump* dumpInfo) {
    assert(deletedNode);

    dumpInfo->nameOfFunc = __func__;
    char beforeMessage[STR_SIZE] =  {};
    char afterMessage[STR_SIZE]= {};
    snprintf(beforeMessage, sizeof(beforeMessage), "BEFORE delete element [%p]", deletedNode);
    snprintf(afterMessage, sizeof(afterMessage), "AFTER delete element  [%p]", deletedNode);

    if(classicListVerifier(cList, dumpInfo)) {
        classicListDump(cList, dumpInfo, beforeMessage);
        return cList->errorCode;
    }

    classicListDump(cList, dumpInfo, beforeMessage);

    listNode_t* prevNode = *(nodePrev(deletedNode));
    listNode_t* nextNode = *(nodeNext(deletedNode));

    *(nodeNext(prevNode)) = nextNode;
    *(nodePrev(nextNode)) = prevNode;

    free(deletedNode);
    *cListSize(cList) -= 1;

    if(classicListVerifier(cList, dumpInfo)) {
        classicListDump(cList, dumpInfo, afterMessage);
        return cList->errorCode;
    }

    classicListDump(cList, dumpInfo, afterMessage);

    return 0;
}

listNode_t* classicListCtor(struct classicList* cList) {
    *cListFictitious(cList) = newListNode (NULL_CANARY);

    listNode_t* fictitiousNode = *cListFictitious(cList);

    *(nodePrev(fictitiousNode)) = fictitiousNode;
    *(nodeNext(fictitiousNode)) = fictitiousNode;

    *cListSize(cList) = 0;
    cList->errorCode = 0;

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
        /*if(node != *(nodePrev(nextNum))) {
            fclose(graphFile);
            reversedClassicListGraphDump (fictitiousNode, textGraphFileName);;
            break;
        }*/
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
        if ((node == badNode1) || (node == badNode2))
            break;
        /*for (listNode_t* node1 = fictitiousNode; ; node1 = *(nodePrev(node1))) {
            fillColor = "#C2BBBD";
            if (*(nodePrev(node1)) == fictitiousNode)
                fillColor = "#79D47F";

            if (*(nodeNext(node1)) == fictitiousNode)
                fillColor = "#E07397";

            if (*(nodeData(node1)) == NULL_CANARY) {
            fprintf(graphFile, "    node%p [label = \" address = %p| data = CANARY|    next = %p| prev = %p\", style = filled, fillcolor = \"#dec84cff\", color = black];\n",
                node, node, *(nodeNext(node)), *(nodePrev(node)));

            if ((*(nodeNext(node1)) == fictitiousNode))
                break;
            continue;
            }

            fprintf(graphFile, "    node%p [label = \" address = %p| data = %d|    next = %p| prev = %p\", style = filled, fillcolor = \"%s\", color = black];\n",
                    node1, node1, *(nodeData(node1)), *(nodeNext(node1)), *(nodePrev(node1)), fillColor);

            if ((*(nodePrev(node1)) == fictitiousNode))
                break;
            if (nodePrev(node1) == NULL)
                break;
            if (((node1) == badNode1) || ((node1) == badNode2))
                break;
        }*/
        //    break;
        //}

    }
$$
    fprintf(graphFile, "\n");
$$
    for (listNode_t* node = fictitiousNode; ; node = *(nodeNext(node))) {
        fprintf(graphFile, "    node%p -> node%p [weight = 500, style = invis, color = white];\n", node, *(nodeNext(node)));
        listNode_t* nextNum = *(nodeNext(node));
        if (nextNum == NULL)
            continue;
        //if(node != *(nodePrev(nextNum)))
        //    break;
        listNode_t* prevNum = *(nodePrev(node));
        if (nextNum == NULL)
            continue;
        if(node != *(nodeNext(prevNum)))
            badNode2 = prevNum;

        if ((*(nodeNext(*(nodeNext(node)))) == fictitiousNode))
            break;

        if ((node == badNode1) || (node == badNode2))
            break;
           /* for (listNode_t* node1 = fictitiousNode; ; node1 = *(nodePrev(node1))) {
                fprintf(graphFile, "    node%p -> node%p [weight = 500, style = invis, color = white];\n", node1, *(nodeNext(node1)));
            if ((*(nodePrev(node1)) == fictitiousNode))
                break;
            if (nodePrev(node1) == NULL)
                break;
            if (((node1) == badNode1) || ((node1) == badNode2))
                break;
            }*/
            //break;
        //}
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
        //if(node != *(nodePrev(nextNum)))
        //    break;
        listNode_t* prevNum = *(nodePrev(node));
        if (nextNum == NULL)
            continue;
        if(node != *(nodeNext(prevNum)))
            badNode2 = prevNum;

        if ((*(nodeNext(node)) == fictitiousNode))
            break;

        if ((*nodeNext(node) == badNode1) || (*nodeNext(node) == badNode2))
            break;
            /*for (listNode_t* node1 = fictitiousNode; ; node1 = *(nodePrev(node1))) {
                listNode_t* nextNum1 = *(nodeNext(node1));
                if(node1 == *(nodePrev(nextNum1)))
                    fprintf(graphFile, "    node%p -> node%p [dir = both, color = \"#9faafaff\"];\n",  node1, nextNum1);
                else {
                    fprintf(graphFile, "    node%p -> node%p [color = \"#220ff5ff\"];\n", node1, nextNum1);
                    fprintf(graphFile, "    errorNode%p [shape = doubleoctagon, style = filled, fillcolor = \"#ff0000ff\",  color = \"#ff0000ff\", label = \" address = %p\", fontcolor = white];\n", *(nodePrev(nextNum1)), *(nodePrev(nextNum1)));
                    fprintf(graphFile, "    node%p -> errorNode%p [color = \"#ff0000ff\", penwidth = 4];\n", nextNum1, *(nodePrev(nextNum1)));
                }

            if ((*(nodePrev(node1)) == fictitiousNode))
                break;
            if (nodePrev(node1) == NULL)
                break;
            if ((*nodePrev(node1) == badNode1) || (*nodePrev(node1) == badNode2))
                break;
            }
            break;
        }*/
    }

    fprintf(graphFile, " }\n");
    fclose(graphFile);
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

int classicListVerifier (struct classicList* cList, struct dump* dumpInfo) {
    assert(cList);
    assert(dumpInfo);

    if (noNextAndPrevMatch(*(cListFictitious(cList))))
        cList->errorCode |= -badNextAndPrevMatch;

    //if (classicListNodeCycle(node))
    //    cList->errorCode |= -badNodeCycle;

    if (findCListBadNextCycle(cList))
        cList->errorCode |= -cListNextBadCycle;

    if (findCListBadPrevCycle(cList))
        cList->errorCode |= -cListPrevBadCycle;

    return cList->errorCode;
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

void classicListDump (struct classicList* cList, struct dump* dumpInfo, const char* message) {
    assert(dumpInfo);
    assert(message);
    assert(cList);

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

    fprintfClassicListErrorsForDump (cList, dumpFile, dumpInfo);

if (!(cList->errorCode & -badNodeCycle) && !(cList->errorCode & -badNextAndPrevMatch))
    fprintfClassicListDataForDump (cList, dumpInfo, dumpFile);

    createClassicListGraphImageForDump (cList, dumpInfo, dumpFile, nameOfTextGraphFile);
$$
    if (fclose(dumpFile) != 0) {
        fprintf(stderr, "Error of closing file \"%s\"", dumpInfo->nameOfGraphFile);
        perror("");
        return;
    }
}

void fprintfClassicListDataForDump (struct classicList* cList, struct dump* dumpInfo, FILE* dumpFile) {
    assert(dumpInfo);
    assert(dumpFile);
    assert(cList);

    fprintf(dumpFile, "errorCode == %d\n\n", cList->errorCode);

    fprintf(dumpFile, "address:  ");
    for (listNode_t* node = *cListFictitious(cList); (node != NULL) && (*(nodeNext(node)) != *cListFictitious(cList)); node = *(nodeNext(node))) {
        fprintf(dumpFile, "[ %9p ]", node);

        if(nodeNext(node) == NULL)
            break;
    }
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "data:     ");
    for (listNode_t* node = *cListFictitious(cList); (node != NULL) && (*(nodeNext(node)) != *cListFictitious(cList)); node = *(nodeNext(node))) {
        if(nodeData(node) == NULL)
            break;
        fprintf(dumpFile, "[ %9d ]", *(nodeData(node)));

        if(nodeNext(node) == NULL)
            break;
    }
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "next:     ");
    for (listNode_t* node = *cListFictitious(cList); (node != NULL) && (*(nodeNext(node)) != *cListFictitious(cList)); node = *(nodeNext(node))) {
        if(nodeNext(node) == NULL)
            break;
        fprintf(dumpFile, "[ %9p ]", *(nodeNext(node)));

        if(nodeNext(node) == NULL)
            break;
    }
    fprintf(dumpFile, "\n");

    fprintf(dumpFile, "prev:     ");
     for (listNode_t* node = *cListFictitious(cList); (node != NULL) && (*(nodeNext(node)) != *cListFictitious(cList)); node = *(nodeNext(node))) {
        if(nodePrev(node) == NULL)
            break;
        fprintf(dumpFile, "[ %9p ]", *(nodePrev(node)));

        if(nodeNext(node) == NULL)
            break;
    }
    fprintf(dumpFile, "\n");
}

void createClassicListGraphImageForDump (struct classicList* cList, struct dump* dumpInfo, FILE* dumpFile, const char* nameOfTextGraphFile) {
    assert(dumpInfo);
    assert(dumpFile);
    assert(nameOfTextGraphFile);
$$
    static int graphImageCounter = 0;
    graphImageCounter++;
$$
    printf("fictitiousNode == %p\n", *cListFictitious(cList));

    if (!(cList->errorCode & -cListPrevBadCycle) && (cList->errorCode & -cListNextBadCycle))
        reversedClassicListGraphDump (*cListFictitious(cList), nameOfTextGraphFile);
    else
        classicListGraphDump(*cListFictitious(cList), nameOfTextGraphFile);

$$
    char graphvizCallCommand[STR_SIZE] = {};
    printf("nameOfTextGraphFile == %s\n", nameOfTextGraphFile);
    snprintf(graphvizCallCommand, sizeof(graphvizCallCommand), "dot -Tpng %s -o GRAPH_DUMPS/graph%d.png", nameOfTextGraphFile, graphImageCounter);
    system(graphvizCallCommand);
    fprintf(dumpFile, "Image:\n <img src=GRAPH_DUMPS/graph%d.png width=1000>\n", graphImageCounter);
}

void fprintfClassicListErrorsForDump (struct classicList* cList, FILE* dumpFile, struct dump* dumpInfo) {
    assert(dumpFile);
    assert(dumpInfo);

    if (cList->errorCode & -badNodeCycle) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! BAD NODE CYCLE! errorcode = %d</font></h2>\n", badNodeCycle);
        printf("ERROR! BAD NODE CYCLE! errorcode = %d; In func %s from %s:%d\n",
        badNodeCycle, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (cList->errorCode & -badNextAndPrevMatch) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! NEXT VALUES DO NOT MATCH WITH PREV! errorcode = %d</font></h2>\n",
        badNextAndPrevMatch);
        printf("ERROR! NEXT VALUES DO NOT MATCH WITH PREV! errorcode = %d; In func %s from %s:%d\n",
        badNextAndPrevMatch, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }//

    if (cList->errorCode & -cListNextBadCycle) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! FIND BAD NEXT CYCLE! errorcode = %d</font></h2>\n",
        cListNextBadCycle);
        printf("ERROR! FIND BAD NEXT CYCLE! errorcode = %d; In func %s from %s:%d\n",
        cListNextBadCycle, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }

    if (cList->errorCode & -cListPrevBadCycle) {
        fprintf(dumpFile, "<h2><font color=red>ERROR! FIND BAD PREV CYCLE!  errorcode = %d</font></h2>\n",
        cListPrevBadCycle);
        printf("ERROR! FIND BAD PREV CYCLE! errorcode = %d; In func %s from %s:%d\n",
        cListPrevBadCycle, dumpInfo->nameOfFunc, dumpInfo->nameOfFile, dumpInfo->numOfLine);
    }
}



int reversedClassicListGraphDump (listNode_t* fictitiousNode, const char* textGraphFileName) {
    assert(fictitiousNode);
    assert(textGraphFileName);

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

    for (listNode_t* node = fictitiousNode; ; node = *(nodePrev(node))) {

        const char* fillColor = "#C2BBBD";

        if (*(nodePrev(node)) == fictitiousNode)
            fillColor = "#79D47F";

        if (*(nodeNext(node)) == fictitiousNode)
            fillColor = "#E07397";

        if (*(nodeData(node)) == NULL_CANARY) {
            fprintf(graphFile, "    node%p [label = \" address = %p| data = CANARY|    next = %p| prev = %p\", style = filled, fillcolor = \"#dec84cff\", color = black];\n",
                node, node, *(nodeNext(node)), *(nodePrev(node)));

            if ((*(nodePrev(node)) == fictitiousNode))
                break;
            continue;
        }


        /*listNode_t* nextNum = *(nodeNext(node));
        if (nextNum == NULL)
            continue;

        listNode_t* prevNum = *(nodePrev(node));
        if (nextNum == NULL)
            continue;
        if(node != *(nodeNext(prevNum)))
            badNode2 = prevNum;*/

        fprintf(graphFile, "    node%p [label = \" address = %p| data = %d|    next = %p| prev = %p\", style = filled, fillcolor = \"%s\", color = black];\n",
                node, node, *(nodeData(node)), *(nodeNext(node)), *(nodePrev(node)), fillColor);

        if (nodePrev(node) == NULL)
            break;
        if ((*(nodePrev(node)) == fictitiousNode))
            break;
    }
$$
    fprintf(graphFile, "\n");
$$
    for (listNode_t* node = fictitiousNode; ; node = *(nodePrev(node))) {
        fprintf(graphFile, "    node%p -> node%p [weight = 500, style = invis, color = white];\n", node, *(nodeNext(node)));
        listNode_t* nextNum = *(nodeNext(node));
        if (nextNum == NULL)
            continue;
        listNode_t* prevNum = *(nodePrev(node));
        if (nextNum == NULL)
            continue;
        if(node != *(nodeNext(prevNum)))
            badNode2 = prevNum;

        if ((*(nodePrev(*(nodePrev(node)))) == fictitiousNode))
            break;
    }

    for (listNode_t* node = fictitiousNode; ; node = *(nodePrev(node))) {

        listNode_t* nextNum = *(nodeNext(node));

        if (nextNum == NULL)
            continue;

        if(node == *(nodePrev(nextNum)))
            fprintf(graphFile, "    node%p -> node%p [dir = both, color = \"#9faafaff\"];\n", node, nextNum);
        else {
            fprintf(graphFile, "    node%p -> node%p [color = \"#220ff5ff\"];\n", node, nextNum);
            fprintf(graphFile, "    errorNode%p [shape = doubleoctagon, style = filled, fillcolor = \"#ff0000ff\",  color = \"#ff0000ff\", label = \" address = %p\", fontcolor = white];\n", nextNum, *(nodePrev(nextNum)));
            fprintf(graphFile, "    node%p -> errorNode%p [color = \"#ff0000ff\", penwidth = 4];\n", nextNum, nextNum);
        }
        //if (nextNum == NULL)
        //    continue;
        //listNode_t* prevNum = *(nodePrev(node));
        //if (nextNum == NULL)
        //    continue;
        //if(node != *(nodeNext(prevNum)))
        //    badNode2 = prevNum;

        if ((*(nodePrev(node)) == fictitiousNode))
            break;

    }

    fprintf(graphFile, " }\n");
    fclose(graphFile);
    return 0;
}


listErr_t findCListBadNextCycle (struct classicList* cList) {
    assert(cList);

    size_t cycleCounter = 0;

    for (listNode_t* node = (*cListFictitious(cList)); cycleCounter < MAX_CAPACITY; ) {
        if (nodeNext(node) == NULL)
            return badNodeCycle;

        if (*(nodeNext(node)) == (*cListFictitious(cList)))
            break;
        cycleCounter++;
        node = *(nodeNext(node));
    }

    if(cycleCounter != *cListSize(cList))
        return cListNextBadCycle;

    return noErrors;
}

listErr_t findCListBadPrevCycle (struct classicList* cList) {
    assert(cList);

    size_t cycleCounter = 0;

    for (listNode_t* node = (*cListFictitious(cList)); cycleCounter < MAX_CAPACITY; ) {
        if (nodeNext(node) == NULL)
            return badNodeCycle;

        if (*(nodePrev(node)) == (*cListFictitious(cList)))
            break;
        cycleCounter++;
        node = *(nodePrev(node));
    }

    if(cycleCounter != *cListSize(cList))
        return cListPrevBadCycle;

    return noErrors;
}
