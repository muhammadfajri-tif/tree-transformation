// #include "includes/boolean.h"
#include <stdbool.h>
#include "file.h"
#include "includes/config.h"
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool fileExists(char filename[])
{
  FILE *file;
  if (strcmp(filename, "\n") == 0 || strcmp(filename, "") == 0)
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
  char bufferName[30];
  bool error = false;

  // empty string for filename will create default file
  if (strcmp(filename, "\n") == 0 || strcmp(filename, "") == 0)
  {
    printf("\nMasuk If\n");
    strcpy(bufferName, DEFAULT_TREE_FILE);
  }
  else
  {
    printf("\nMasuk Else\n");
    strcpy(bufferName, filename);
  }

  printf("Buffer Name: %s\n", bufferName);
  printf("Filename: %s\n", filename);

  file = fopen(bufferName, mode);
  if (file == NULL)
  {
    printHalfScreen("\033[1;33m[WARN]\t\033[1;0mFile untuk menyimpan Tree tidak dapat ditemukan!", true, false);
    printHalfScreen("\033[1;34m[INFO]\t\033[1;0mMembuat file untuk menyimpan Tree.", true, false);

    file = fopen(bufferName, "wb");

    if (file == NULL)
      error = true;

    if (!error)
    {
      char bufferMessage[75] = "\033[1;34m[INFO]\t\033[1;0mBerhasil membuat file '";
      printHalfScreen(strcat(strcat(bufferMessage, bufferName), "'."), true, false);
    }
  }

  if (error)
    // Please check your storage's or file's permission
    printHalfScreen("\033[1;31m[ERR]\t\033[1;0mGagal membuat file. Periksa kembali penyimpanan dan/atau perizinan file pada penyimpanan.", true, false);

  return file;
}

void loadNodesTree(char filename[], Tree *nbtree)
{
  FILE *file;
  if (strcmp(filename, "\n") == 0)
  {
    file = accessFile(DEFAULT_TREE_FILE, "rb");
  }
  else
  {
    file = accessFile(filename, "rb");
  }

  char bufferInfo;
  char bufferParent;
  char bufferMessage[128];
  int totalNode = 0;

  while (fscanf(file, "%c,%c;", &bufferInfo, &bufferParent) != EOF)
  {
    if (totalNode == 0)
    {
      nbtree->root = allocate(bufferInfo);
      nbtree->isBinary = false;
      nbtree->isAVL = false;

      snprintf(bufferMessage, sizeof(bufferMessage), "> Node '%c' sebagai root Tree berhasil dimuat.", bufferInfo);
      printHalfScreen(bufferMessage, true, false);
    }
    else
    {
      insertNBTNode(nbtree, bufferInfo, bufferParent);

      snprintf(bufferMessage, sizeof(bufferMessage), "> Node '%c' dengan parent '%c' berhasil dimuat.", bufferInfo, bufferParent);
      printHalfScreen(bufferMessage, true, false);
    }
    totalNode++;
  }

  snprintf(bufferMessage, sizeof(bufferMessage), "\033[1;34m[INFO]\t\033[1;0mBerhasil memuat Tree dari file '%s' dengan total %d node.", (strcmp(filename, "\n") == 0) ? DEFAULT_TREE_FILE : filename, totalNode);
  printHalfScreen(bufferMessage, true, false);
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

  char bufferMessage[36] = "> Menyimpan Node '";
  snprintf(bufferMessage, sizeof(bufferMessage), "> Menyimpan Node '%c' kedalam file.", Info(node));
  printHalfScreen(bufferMessage, true, false);
}

void saveNodesTree(char filename[], Tree tree, address node)
{
  if (node == NULL)
  {
    // printHalfScreen("\n\033[1;34m[INFO]\t\033[1;0mBerhasil menyimpan data Tree ke dalam file.", true, false);
    return;
  }

  appendNodeTree(filename, tree, node);
  saveNodesTree(filename, tree, LeftSon(node));  // left son
  saveNodesTree(filename, tree, RightSon(node)); // right son
}
