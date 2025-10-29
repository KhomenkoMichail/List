#ifndef LIST_ACCESS_FUNCTIONS_H
#define LIST_ACCESS_FUNCTIONS_H

int* listHead (struct list* lst);

int* listTail (struct list* lst);

size_t* listFree (struct list* lst);

int* listNext (struct list* lst, size_t numOfNode);

int* listPrev (struct list* lst, size_t numOfNode);

int* listData (struct list* lst, size_t numOfNode);

size_t* listSize (struct list* lst);

#endif
