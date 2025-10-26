#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H
#include"structsAndConsts.h"

#define LIST_CTOR(listName, capacity, listInfo)\
    listInfo.name = #listName;\
    listInfo.nameOfFile = __FILE__;\
    listInfo.nameOfFunc = __func__;\
    listInfo.numOfLine = __LINE__;\
    listCtor(&listName, capacity, listInfo);\

void listCtor (struct list* lst, ssize_t capacity, struct info listInfo);

int insortAfter (struct list* lst, size_t anchorElemNum, listData_t dataValue);

int deleteElem (struct list* lst, size_t deletedElem);

int reallocList (struct list* lst);

int fprintfGraphDump (struct list* lst, const char* textGraphFileName);

int fprintfGraphDump2 (struct list* lst, const char* textGraphFileName);

#endif
