#ifndef LIST_FUNCTIONS_H
#define LIST_FUNCTIONS_H

#include"structsAndConsts.h"

#define LIST_CTOR(listName, capacity, listInfo)\
    (listInfo).name = #listName;\
    (listInfo).nameOfFile = __FILE__;\
    (listInfo).nameOfFunc = __func__;\
    (listInfo).numOfLine = __LINE__;\
    listCtor(&listName, capacity, listInfo);\

#define InsertAfter(listAddress, anchorElemNum, dataValue, dumpInfoAddress) ({\
    (dumpInfoAddress)->nameOfFile = __FILE__;\
    (dumpInfoAddress)->numOfLine = __LINE__;\
    int returnableValue = insertAfter(listAddress, anchorElemNum, dataValue, dumpInfoAddress);\
    returnableValue;\
})

#define DeleteElement(listAddress, deletedElement, dumpInfoAddress) ({\
    (dumpInfoAddress)->nameOfFile = __FILE__;\
    (dumpInfoAddress)->numOfLine = __LINE__;\
    int returnableValue = deleteElement(listAddress, deletedElement, dumpInfoAddress);\
    returnableValue;\
})

void listCtor (struct list* lst, ssize_t capacity, struct info listInfo);

listErr_t reallocList (struct list* lst);

int fprintfGraphDump (struct list* lst, const char* textGraphFileName);

int listVerifier (struct list* lst);

void listDump (struct list* lst, struct dump* dumpInfo, const char* message);

void fprintfListDataForDump (struct list* lst, FILE* dumpFile);

void createGraphImageForDump (struct list* lst, FILE* dumpFile, const char* nameOfTextGraphFile);

int findBadFreeNode (struct list* lst);

int findBadNextAndPrevMatch (struct list* lst);

void fprintfListErrorsForDump (struct list* lst, FILE* dumpFile);

int insertAfter (struct list* lst, size_t anchorElemNum, listData_t dataValue, struct dump* dumpInfo);

int insertBefore (struct list* lst, size_t anchorElemNum, listData_t dataValue, struct dump* dumpInfo);

int deleteElement (struct list* lst, size_t deletedElement, struct dump* dumpInfo);

listErr_t findBadNodeCycle (struct list* lst);

listErr_t findBadAnchorElemNum (struct list* lst, size_t anchorElemNum, struct dump* dumpInfo);

listErr_t findBadDeleteNum (struct list* lst, size_t deletedElement, struct dump* dumpInfo);

#endif
