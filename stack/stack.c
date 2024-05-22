#include "stack.h"

void push(List *L, infotypeP X){
    InsVFirst(L, X);
}

void pop(List *L){
    infotypeP X;
    DelVFirst(L, &X);
}

infotypeP top(List L){
    return Info(First(L));
}

infotypeP pull(List *L){
    infotypeP X;
    DelVFirst(L, &X);
    return X;
}