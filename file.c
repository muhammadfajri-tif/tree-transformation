#include "includes/boolean.h"
#include "file.h"
#include "includes/config.h"
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

boolean fileExists(char filename[])
{
  FILE *file;
  if (strcmp(filename, "\n") == 0)
    file = fopen(DEFAULT_TREE_FILE, "rb");
  else
    file = fopen(filename, "rb");

  if (file == NULL)
    return false;

  fclose(file);
  return true;
}

FILE *accessFile(char filename[], char mode[])
{
  FILE *file;
  char *bufferName;
  boolean error = false;

  // empty string for filename will create default file
  if (strcmp(filename, "\n") == 0)
  {
    bufferName = (char *)malloc((sizeof(char) * strlen(DEFAULT_TREE_FILE)) + sizeof(char));
    strcpy(bufferName, DEFAULT_TREE_FILE);
  }
  else
  {
    bufferName = (char *)malloc(sizeof(char) * strlen(filename));
    strcpy(bufferName, filename);
  }

  file = fopen(bufferName, mode);
  if (file == NULL)
  {
    printf("\033[1;33m[WARN]\t\033[1;0mFile untuk menyimpan Tree tidak dapat ditemukan!\n");
    printf("\033[1;34m[INFO]\t\033[1;0mMembuat file untuk menyimpan Tree.\n");

    file = fopen(bufferName, "wb");

    if (file == NULL)
      error = true;

    if (!error)
      printf("\033[1;34m[INFO]\t\033[1;0mBerhasil membuat file '%s'.\n", bufferName);
  }

  if (error)
    // Please check your storage's or file's permission
    printf("\033[1;31m[ERR]\t\033[1;0mGagal membuat file. Periksa kembali penyimpanan dan/atau perizinan file pada penyimpanan.\n");

  free(bufferName);
  return file;
}

void loadNodesTree(char filename[], Tree *nbtree)
{
  FILE *file;
  if (strcpy(filename, "\n") == 0)
    file = accessFile(DEFAULT_TREE_FILE, "rb");
  else
    file = accessFile(filename, "rb");

  char bufferInfo;
  char bufferParent;
  int totalNode = 0;

  while (fscanf(file, "%c,%c;", &bufferInfo, &bufferParent) != EOF)
  {
    if (totalNode == 0)
    {
      nbtree->root = allocate(bufferInfo);
      nbtree->isBinary = false;
      nbtree->isAVL = false;

      printf("> Node '%c' sebagai root Tree berhasil dimuat.\n", bufferInfo);
    }
    else
    {
      insertNBTNode(nbtree, bufferInfo, bufferParent);
      printf("> Node '%c' dengan parent '%c' berhasil dimuat.\n", bufferInfo, bufferParent);
    }
    totalNode++;
  }

  printf("\033[1;34m[INFO]\t\033[1;0mBerhasil memuat Tree dari file '%s' dengan total %d node.\n", (strcmp(filename, "\n") == 0) ? DEFAULT_TREE_FILE : filename, totalNode);
}

void appendNodeTree(char filename[], Tree tree, address node)
{
  FILE *file;
  if (strcmp(filename, "\n") == 0)
    file = accessFile(DEFAULT_TREE_FILE, "ab");
  else
    file = accessFile(filename, "ab");

  address parent = searchParent(tree, Info(node));
  fprintf(file, "%c,%c;", Info(node), parent == NULL ? '\0' : Info(parent));
  fclose(file);

  printf("> Menyimpan Node '%c' ke dalam file.\n", Info(node));
}

void saveNodesTree(char filename[], Tree tree, address node)
{
  if (node == NULL)
  {
    printf("\n\033[1;34m[INFO]\t\033[1;0mBerhasil menyimpan data Tree ke dalam file.\n");
    return;
  }

  appendNodeTree(filename, tree, node);
  saveNodesTree(filename, tree, LeftSon(node));  // left son
  saveNodesTree(filename, tree, RightSon(node)); // right son
}
