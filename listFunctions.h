#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H

#include"structsAndConsts.h"

#define LIST_CTOR(listName, capacity, listInfo)\
    (listInfo).name = #listName;\
    (listInfo).nameOfFile = __FILE__;\
    (listInfo).nameOfFunc = __func__;\
    (listInfo).numOfLine = __LINE__;\
    listCtor(&listName, capacity, listInfo);\

/*#define LIST_DUMP(listAddress, dumpInfo, message)\
    (dumpInfo).nameOfFile = __FILE__;\
    (dumpInfo).nameOfFunc = __func__;\
    (dumpInfo).numOfLine = __LINE__;\
    listDump (listAddress, &dumpInfo, message);\*/

#define InsortAfter(listAddress, anchorElemNum, dataValue, dumpInfoAddress)\
    (dumpInfoAddress)->nameOfFile = __FILE__;\
    (dumpInfoAddress)->numOfLine = __LINE__;\
    insortAfter2 (listAddress, anchorElemNum, dataValue, dumpInfoAddress);\

#define DeleteElement(listAddress, deletedElement, dumpInfoAddress)\
    (dumpInfoAddress)->nameOfFile = __FILE__;\
    (dumpInfoAddress)->numOfLine = __LINE__;\
    deleteElement2 (listAddress, deletedElement, dumpInfoAddress);\




void listCtor (struct list* lst, ssize_t capacity, struct info listInfo);

//int insortAfter (struct list* lst, size_t anchorElemNum, listData_t dataValue);

//int deleteElement (struct list* lst, size_t deletedElem);

int reallocList (struct list* lst);

int fprintfGraphDump (struct list* lst, const char* textGraphFileName);

int listVerifier (struct list* lst);

//void listDump (struct list* lst, struct dump* dumpInfo);

void listDump (struct list* lst, struct dump* dumpInfo, const char* message);

void fprintfListDataForDump (struct list* lst, FILE* dumpFile);

void createGraphImageForDump (struct list* lst, FILE* dumpFile, const char* nameOfTextGraphFile);

int findBadFreeNode (struct list* lst);

int findBadNextAndPrevMatch (struct list* lst);

void fprintfListErrorsForDump (struct list* lst, FILE* dumpFile);

int insortAfter2 (struct list* lst, size_t anchorElemNum, listData_t dataValue, struct dump* dumpInfo);

int deleteElement2 (struct list* lst, size_t deletedElement, struct dump* dumpInfo);

#endif
