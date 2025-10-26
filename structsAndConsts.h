#ifndef STRUCTS_AND_CONSTS_H
#define STRUCTS_AND_CONSTS_H

const int POISON = 0xBAD;
const int nullData = 0xBABE;

typedef int listData_t;

struct node {
    listData_t data;
    size_t next;
    size_t prev;
};

struct info {
    const char* name;
    const char* nameOfFile;
    const char* nameOfFunc;
    unsigned int numOfLine;
};

struct list {
    struct node* nodeArr;
    size_t head;
    size_t tail;
    size_t free;

    size_t capacity;

    int errorCode;
    struct info creationInfo;
};

enum listErr_t {
    noErrors = 0b0,
    badListPtr= 0b1,
    badNodeArrPtr = 0b10,
    badCapacity = 0b100,
    badNullNode = 0b1000,
    badNextAndPrevMatch = 0b10000,
};

#endif
