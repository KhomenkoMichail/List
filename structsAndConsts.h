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
    noErrors            = 0x00,
    badListPtr          = 0x01,
    badNodeArrPtr       = 0x02,
    badCapacity         = 0x04,
    badNullNode         = 0x08,
    badFreeNode         = 0x10,
    badNextAndPrevMatch = 0x20,
    badHead             = 0x40,
    badTail             = 0x80,
    requestForBadNum    = -3,
};

#endif
