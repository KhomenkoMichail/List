#include <stdio.h>
#include <assert.h>

#include "listAccessFunctions.h"
#include "listFunctions.h"
#include "structsAndConsts.h"

int* listHead (struct list* lst) {
    assert(lst);

    return &(((lst->nodeArr)[0]).next);
}

int* listTail (struct list* lst) {
    assert(lst);

    return &((lst->nodeArr)[0]).prev;
}

size_t* listFree (struct list* lst) {
    assert(lst);

    return &(lst->free);
}

int* listNext (struct list* lst, size_t numOfNode) {
    assert(lst);

    if (numOfNode > lst->capacity) {
        printf("Error! request for too big numberOfNode\n");
        return NULL;
    }

    return &(((lst->nodeArr)[numOfNode]).next);
}

int* listPrev (struct list* lst, size_t numOfNode) {
    assert(lst);

    if (numOfNode > lst->capacity) {
        printf("Error! request for too big numberOfNode\n");
        return NULL;
    }

    return &(((lst->nodeArr)[numOfNode]).prev);
}

int* listData (struct list* lst, size_t numOfNode) {
    assert(lst);

    if (numOfNode > lst->capacity) {
        printf("Error! request for too big numberOfNode\n");
        return NULL;
    }

    return &(((lst->nodeArr)[numOfNode]).data);
}

size_t* listSize (struct list* lst) {
    assert(lst);

    return &(lst->size);
}

size_t* listCapacity (struct list* lst) {
    assert(lst);

    return &(lst->capacity);
}

listData_t* nodeData (listNode_t* node) {
    assert(node);
    if(node == NULL)
        return NULL;

    return &(node->data);
}

listNode_t** nodePrev (listNode_t* node) {
    assert(node);
    if(node == NULL)
        return NULL;

    return &(node->prev);
}

listNode_t** nodeNext (listNode_t* node) {
    assert(node);
    if(node == NULL)
        return NULL;

    return &(node->next);
}
