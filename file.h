#ifndef file_H
#define file_H
#include <stdio.h>

FILE *accessFile(char filename[], char mode[]);

void loadNodesTree(char filename[], Tree tree);

void saveNodesTree(Tree root);

#endif
