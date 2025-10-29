#ifndef STRUCTS_AND_CONSTS_H
#define STRUCTS_AND_CONSTS_H

const int POISON = 0xBAD;
const int NULL_CANARY = 0xBABE;

typedef int listData_t;

struct node {
    listData_t data;
    int next;
    int prev;
};

struct info {
    const char* name;
    const char* nameOfFile;
    const char* nameOfFunc;
    unsigned int numOfLine;

};

struct dump {
    const char* nameOfFile;
    const char* nameOfFunc;
    unsigned int numOfLine;

    const char* nameOfDumpFile;
    const char* nameOfGraphFile;
    int dumpFileWasOpened;
};

struct listFiles {
    const char* nameOfDumpFile;
    const char* nameOfGraphFile;
    FILE* dumpFile;
};

struct list {
    struct node* nodeArr;
//    size_t head;
//    size_t tail;
    size_t free;

    size_t capacity;
    size_t size;

    int errorCode;
    struct info creationInfo;
    struct listFiles files;
};

const size_t MAX_CAPACITY = 5000;

enum listErr_t {
    noErrors = 0b0,
    badListPtr= 0b1,
    badNodeArrPtr = 0b10,
    badCapacity = 0b100,
    badNullNode = 0b1000,
    badFreeNode = 0b10000,
    badNextAndPrevMatch = 0b100000,
    badHead = 0b1000000,
    badTail = 0b10000000,
    requestForBadNum = -3,
};

#endif
