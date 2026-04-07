#ifndef CLASSIC_LIST_FUNCTIONS_H
#define CLASSIC_LIST_FUNCTIONS_H

#define ClassicInsertAfter(cListAddress, anchorNode, dataValue, dumpInfoAddress) ({\
    (dumpInfoAddress)->nameOfFile = __FILE__;\
    (dumpInfoAddress)->numOfLine = __LINE__;\
    listNode_t* returnableValue = classicInsertAfter(cListAddress, anchorNode, dataValue, dumpInfoAddress);\
    returnableValue;\
})

#define ClassicDeleteNode(cListAddress, deletedNode, dumpInfoAddress) ({\
    (dumpInfoAddress)->nameOfFile = __FILE__;\
    (dumpInfoAddress)->numOfLine = __LINE__;\
    int returnableValue = classicDeleteNode(cListAddress, deletedNode, dumpInfoAddress);;\
    returnableValue;\
})

listNode_t* newListNode (listData_t dataValue);

listNode_t* classicInsertAfter (struct classicList* cList, listNode_t* anchorNode, listData_t dataValue, struct dump* dumpInfo);

int classicDeleteNode (struct classicList* cList, listNode_t* deletedNode, struct dump* dumpInfo);

listNode_t* classicListCtor (struct classicList* cList);

int classicListGraphDump (listNode_t* fictitiousNode, const char* textGraphFileName);

void classicListDtor (listNode_t* fictitiousNode);

int noNextAndPrevMatch (listNode_t* startNode);

listErr_t classicListNodeCycle (listNode_t* startNode);

int classicListVerifier (struct classicList* cList, struct dump* dumpInfo);

void classicListDump (struct classicList* cList, struct dump* dumpInfo, const char* message);

void fprintfClassicListDataForDump (struct classicList* cList, struct dump* dumpInfo, FILE* dumpFile);

void createClassicListGraphImageForDump (struct classicList* cList, struct dump* dumpInfo, FILE* dumpFile, const char* nameOfTextGraphFile);

void fprintfClassicListErrorsForDump (struct classicList* cList, FILE* dumpFile, struct dump* dumpInfo);

int reversedClassicListGraphDump (listNode_t* fictitiousNode, const char* textGraphFileName);

listErr_t findCListBadNextCycle (struct classicList* cList);

listErr_t findCListBadPrevCycle (struct classicList* cList);

#endif
