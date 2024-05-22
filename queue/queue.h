#ifndef queue_H
#define queue_H
#include "../linkedlist/linearList.c"

void enqueue(List *L, infotypeP data);

infotypeP dequeue(List *L);

infotypeP getFront(List L);

#endif
