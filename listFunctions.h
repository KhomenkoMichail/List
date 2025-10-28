#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H

#include"structsAndConsts.h"

#define LIST_CTOR(listName, capacity, listInfo)\
    (listInfo).name = #listName;\
    (listInfo).nameOfFile = __FILE__;\
    (listInfo).nameOfFunc = __func__;\
    (listInfo).numOfLine = __LINE__;\
    listCtor(&listName, capacity, listInfo);\

#define LIST_DUMP(listAddress, dumpInfo)\
    (dumpInfo).nameOfFile = __FILE__;\
    (dumpInfo).nameOfFunc = __func__;\
    (dumpInfo).numOfLine = __LINE__;\
    listDump (listAddress, &dumpInfo);\

void listCtor (struct list* lst, ssize_t capacity, struct info listInfo);

int insortAfter (struct list* lst, size_t anchorElemNum, listData_t dataValue);

int deleteElement (struct list* lst, size_t deletedElem);

int reallocList (struct list* lst);

int fprintfGraphDump (struct list* lst, const char* textGraphFileName);

int listVerifier (struct list* lst);

void listDump (struct list* lst, struct dump* dumpInfo);

void fprintfListDataForDump (struct list* lst, FILE* dumpFile);

void createGraphImageForDump (struct list* lst, FILE* dumpFile, const char* nameOfTextGraphFile);

int findBadFreeNode (struct list* lst);

int findBadNextAndPrevMatch (struct list* lst);

void fprintfListErrorsForDump (struct list* lst, FILE* dumpFile);

#endif
