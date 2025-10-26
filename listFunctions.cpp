#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "listFunctions.h"
#include "structsAndConsts.h"

void listCtor (struct list* lst, ssize_t capacity, struct info listInfo) {
    assert(lst);

    lst->nodeArr = (struct node*)calloc(capacity, sizeof(struct node));
    lst->capacity = capacity;

    ((lst->nodeArr)[0]).data = nullData;
    ((lst->nodeArr)[0]).next = 0;
    ((lst->nodeArr)[0]).prev = 0;

    for (size_t nodeNum = 1; nodeNum < capacity; nodeNum++) {
        ((lst->nodeArr)[nodeNum]).data = 0xBAD;
        ((lst->nodeArr)[nodeNum]).next = nodeNum + 1;
        ((lst->nodeArr)[nodeNum]).prev = -1;
    }

    ((lst->nodeArr)[capacity - 1]).next = 0;

    lst->head = 0;
    lst->tail = 0;
    lst->free = 1;

    (lst->creationInfo).name = listInfo.name;
    (lst->creationInfo).nameOfFunc = listInfo.nameOfFunc;
    (lst->creationInfo).nameOfFile = listInfo.nameOfFile;
    (lst->creationInfo).numOfLine = listInfo.numOfLine;

    lst->errorCode = noErrors;
}

int insortAfter (struct list* lst, size_t anchorElemNum, listData_t dataValue) {
    assert(lst);

    struct node* nodes = lst->nodeArr;

    if(lst->free == 0)
        reallocList(lst);
        //continue;   //realloc

    size_t freeNum = lst->free;

    if(anchorElemNum == lst->tail)
        lst->tail = freeNum;

    if((anchorElemNum < lst->head) || (lst->head == 0))
        lst->head = freeNum;

    (nodes[freeNum]).data = dataValue;
    (nodes[freeNum]).prev = anchorElemNum;

    size_t nextFreeNum = (nodes[freeNum]).next;

    (nodes[freeNum]).next = (nodes[anchorElemNum]).next;

    if(anchorElemNum != 0)
        (nodes[anchorElemNum]).next = freeNum;

    size_t nextNumAfterNew = (nodes[freeNum]).next;

    if(nextNumAfterNew != 0)
        (nodes[nextNumAfterNew]).prev = freeNum;

    lst->free = nextFreeNum;

    return 0;
}

int deleteElem (struct list* lst, size_t deletedElem) {
    assert(lst);

    struct node* nodes = lst->nodeArr;

    if(deletedElem == lst->head)
        lst->head = (nodes[deletedElem]).next;

    if(deletedElem == lst->tail)
        lst->tail = (nodes[deletedElem]).prev;

    (nodes[deletedElem]).data = POISON;

    size_t prevElemNum = (nodes[deletedElem]).prev;
    size_t nextElemNum = (nodes[deletedElem]).next;

    if(prevElemNum != 0)
        (nodes[prevElemNum]).next = (nodes[deletedElem]).next;

    (nodes[deletedElem]).next = lst->free;
    lst->free = deletedElem;

    if (nextElemNum != 0)
        (nodes[nextElemNum]).prev = prevElemNum;
    (nodes[deletedElem]).prev = -1;

    return 0;
}

int reallocList (struct list* lst) {
    assert(lst);

    lst->capacity *= 2;

    realloc(lst->nodeArr, (lst->capacity)*sizeof(struct node));

    for (size_t nodeNum = lst->capacity / 2; nodeNum < lst->capacity; nodeNum++) {
        ((lst->nodeArr)[nodeNum]).data = 0xBAD;
        ((lst->nodeArr)[nodeNum]).next = nodeNum + 1;
        ((lst->nodeArr)[nodeNum]).prev = -1;
    }

    ((lst->nodeArr)[lst->capacity - 1]).next = 0;

    lst->free = lst->capacity / 2;

    return 0;
}

/*int listVerifier (struct list* lst) {
    if (stackPtrIsNull (stack, stdout))
        return badStackPtr;

    if (stack->data == NULL)
        stack->errorCode |= badDataPtr;

    if ((stack->size < 0) || ((stack->size > stack->capacity) && (stack->capacity >= 0))  || (stack->size > MAX_CAPACITY))
        stack->errorCode |= badSize;

    if ((stack->capacity <= 0) || (stack->capacity > MAX_CAPACITY))
        stack->errorCode |= badCapacity;

    return stack->errorCode;
}*/






