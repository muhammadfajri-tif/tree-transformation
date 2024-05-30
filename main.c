// #include "./includes/boolean.h"
#include "body.c"
#include "display.c"
#include "file.c"
#include <stdio.h>

int main(int argc, char *argv[])
{
  Tree nbtree;
  Tree btree;
  Tree tAVL;
  int treeType = NONBINARYTREE;
  createTreeMenu(&nbtree, &btree, &tAVL, &treeType);

  return 0;
} 