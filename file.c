#include "file.h"
#include "includes/boolean.h"
#include "includes/config.h"
#include <stdio.h>
#include <string.h>

FILE *accessFile(char filename[], char mode[]) {
  FILE *file;

  // empty string for filename will create default file
  if (strcmp(filename, "") == 0)
    file = fopen(DEFAULT_TREE_FILE, mode);
  else
    file = fopen(DEFAULT_TREE_FILE, mode);

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
