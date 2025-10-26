#include <stdio.h>

#include "listFunctions.h"
#include "structsAndConsts.h"

int main (void) {
    struct list lst = {};
    struct info listInfo = {};

    LIST_CTOR(lst, 5, listInfo);
    //listCtor(&lst, 5);

    printf ("%s\n", lst.creationInfo.name);
    printf ("%s\n", lst.creationInfo.nameOfFunc);
    printf ("%s\n", lst.creationInfo.nameOfFile);
    printf ("%d\n", lst.creationInfo.numOfLine);


    printf("data[%d] == %d\n", 0, ((lst.nodeArr)[0]).data);
    printf("next[%d] == %d\n", 0, ((lst.nodeArr)[0]).next);
    printf("prev[%d] == %d\n\n", 0, ((lst.nodeArr)[0]).prev);
    getchar();

    insortAfter (&lst, 0, 10);
    insortAfter (&lst, 1, 20);
    insortAfter (&lst, 2, 30);
    insortAfter (&lst, 3, 40);
    //insortAfter (&lst, 4, 50);

    printf("data[%d] == %d\n", 0, ((lst.nodeArr)[0]).data);
    printf("next[%d] == %d\n", 0, ((lst.nodeArr)[0]).next);
    printf("prev[%d] == %d\n\n", 0, ((lst.nodeArr)[0]).prev);
    getchar();



    for(int i = 1; ; i = ((lst.nodeArr)[i]).next) {
        printf("data[%d] == %d\n", i, ((lst.nodeArr)[i]).data);
        printf("next[%d] == %d\n", i, ((lst.nodeArr)[i]).next);
        printf("prev[%d] == %d\n\n", i, ((lst.nodeArr)[i]).prev);
        printf("free = %d\n", lst.free);
        printf("tail = %d\n", lst.tail);
        printf("head = %d\n", lst.head);
        if (i == lst.tail)
            break;
        getchar();
    }

    insortAfter (&lst, 4, 50);

    for(int i = 1; ; i = ((lst.nodeArr)[i]).next) {
        printf("data[%d] == %d\n", i, ((lst.nodeArr)[i]).data);
        printf("next[%d] == %d\n", i, ((lst.nodeArr)[i]).next);
        printf("prev[%d] == %d\n\n", i, ((lst.nodeArr)[i]).prev);
        printf("free = %d\n", lst.free);
        printf("tail = %d\n", lst.tail);
        printf("head = %d\n", lst.head);
        if (i == lst.tail)
            break;
        getchar();
    }

    for (int i = 0; i < 10; i++) {
        printf("data[%d] == %d\n", i, ((lst.nodeArr)[i]).data);
        printf("next[%d] == %d\n", i, ((lst.nodeArr)[i]).next);
        printf("prev[%d] == %d\n\n", i, ((lst.nodeArr)[i]).prev);
        printf("free = %d\n\n", lst.free);
        getchar();
    }


}
