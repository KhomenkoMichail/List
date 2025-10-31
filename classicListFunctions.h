#ifndef CLASSIC_LIST_FUNCTIONS_H
#define CLASSIC_LIST_FUNCTIONS_H

#define ClassicInsertAfter(anchorNode, dataValue, dumpInfoAddress) ({\
    (dumpInfoAddress)->nameOfFile = __FILE__;\
    (dumpInfoAddress)->numOfLine = __LINE__;\
    listNode_t* returnableValue = classicInsertAfter(anchorNode, dataValue, dumpInfoAddress);\
    returnableValue;\
})

#define ClassicDeleteNode(deletedNode, dumpInfoAddress) ({\
    (dumpInfoAddress)->nameOfFile = __FILE__;\
    (dumpInfoAddress)->numOfLine = __LINE__;\
    int returnableValue = classicDeleteNode(deletedNode, dumpInfoAddress);;\
    returnableValue;\
})

listNode_t* newListNode (listData_t dataValue);

listNode_t* classicInsertAfter (listNode_t* anchorNode, listData_t dataValue, struct dump* dumpInfo);

int classicDeleteNode (listNode_t* deletedNode, struct dump* dumpInfo);

listNode_t* classicListCtor (void);

int classicListGraphDump (listNode_t* fictitiousNode, const char* textGraphFileName);

void classicListDtor (listNode_t* fictitiousNode);

int noNextAndPrevMatch (listNode_t* startNode);

listErr_t classicListNodeCycle (listNode_t* startNode);

int classicListVerifier (listNode_t* node, struct dump* dumpInfo);

void classicListDump (struct dump* dumpInfo, const char* message);

void fprintfClassicListDataForDump (struct dump* dumpInfo, FILE* dumpFile);

void createClassicListGraphImageForDump (struct dump* dumpInfo, FILE* dumpFile, const char* nameOfTextGraphFile);

void fprintfClassicListErrorsForDump (FILE* dumpFile, struct dump* dumpInfo);

#endif
