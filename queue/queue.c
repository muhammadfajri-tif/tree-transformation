#include "queue.h"

void enqueue(List *L, infotypeP data)
{
    InsVLast(L, data);
}

infotypeP dequeue(List *L){
    infotypeP data;
    DelVFirst(L, &data);
    return data;
}

infotypeP getFront(List L){
    return L.First->info;
}