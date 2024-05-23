#ifndef file_H
#define file_H
#include <stdio.h>

boolean fileExists(char filename[]);

FILE *accessFile(char filename[], char mode[]);

void loadNodesTree(char filename[], Tree *nbtree);

void appendNodeTree(char filename[], Tree tree, address node);

void saveNodesTree(char filename[], Tree tree, address node);

#endif
