// #include "file.h"
#include "includes/boolean.h"
#include "includes/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *accessFile(char filename[], char mode[]) {
  FILE *file;

  // empty string for filename will create default file
  if (strcmp(filename, "") == 0)
    file = fopen(DEFAULT_TREE_FILE, mode);
  else
    file = fopen(filename, mode);

  boolean error = false;

  if (file == NULL) {
    printf("\033[1;33m[WARN]\t\033[1;0mFile untuk menyimpan Tree tidak dapat "
           "ditemukan!\n");
    printf("\033[1;34m[INFO]\t\033[1;0mMembuat file untuk menyimpan Tree.\n");

    if (strcmp(filename, "") == 0)
      file = fopen(DEFAULT_TREE_FILE, "wb");
    else
      file = fopen(filename, "wb");

    if (file == NULL)
      error = true;

    if (!error)
      printf("\033[1;34m[INFO]\t\033[1;0mBerhasil membuat file '%s'.\n",
             DEFAULT_TREE_FILE);
  }

  if (error) {
    // Please check your storage's or file's permission
    printf("\033[1;31m[ERR]\t\033[1;0mGagal membuat file. Periksa kembali "
           "penyimpanan dan/atau perizinan file pada penyimpanan.\n");
    exit(1);
  }
  return file;
}

// TODO: Change int tree to Tree nbtree
void loadNodesTree(char filename[], int nbtree) {
  FILE *file = accessFile(filename, "rb");
  char bufferInfo;
  char bufferLeft;
  char bufferRight;
  int totalNode = 0;

  while (fscanf(file, "%c,%c,%c;", &bufferInfo, &bufferLeft, &bufferRight) !=
         EOF) {
    // ALGORITHM:
    // find first char in tree
    // if found create node, left node, and right node
    // if not found only attach left node, and right node

    totalNode++;
  }
}

// TODO: Change int tree to Tree root
void appendNodeTree(char filename[], int *node) {
  char bufferInfo = '\0';
  char bufferLeft = '\0';
  char bufferRight = '\0';

  FILE *file = accessFile(filename, "ab");

  // validation
  // // TODO: Adjust this
  // if (strcmp(node->info, "") != 0)
  //   bufferInfo = 'I';
  // if (node->left != NULL)
  //   bufferLeft = 'L';
  // if (node->right != NULL)
  //   bufferRight = 'R';

  // TODO: change to node->info
  fprintf(file, "%c,%c,%c;", 'I', 'L', 'R');
  fclose(file);

  // TODO: change to %s Node->Info
  printf("[INFO] Berhasil menyimpan Node '%i' ke dalam file.\n", *node);
}

// TODO: Change int tree to Tree root
void saveNodesTree(char filename[], int *root) {
  if (root == NULL)
    return;

  appendNodeTree(filename, root);
  saveNodesTree(filename, root); // left son
  saveNodesTree(filename, root); // right son
}
