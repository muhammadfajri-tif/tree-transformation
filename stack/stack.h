#ifndef stack_H
#define stack_H
#include "../queue/queue.c"

void push(List *L, infotypeP X);

void pop(List *L);

infotypeP top(List L);

infotypeP pull(List *L);

#endif
