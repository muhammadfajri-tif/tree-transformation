#ifndef file_H
#define file_H
#include <stdio.h>

FILE *accessFile(char filename[], char mode[]);

void loadNodesTree(char filename[], Tree nbtree);

void saveNodesTree(char filename[], Tree root);

#endif
