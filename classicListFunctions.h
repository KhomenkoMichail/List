#ifndef CLASSIC_LIST_FUNCTIONS_H
#define CLASSIC_LIST_FUNCTIONS_H

listNode_t* newListNode (listData_t dataValue);

listNode_t* classicInsertAfter (listNode_t* anchorNode, listData_t dataValue);

int classicDeleteNode (listNode_t* deletedNode);

listNode_t* classicListCtor(void);

int classicListGraphDump (listNode_t* fictitiousNode, const char* textGraphFileName);

#endif
