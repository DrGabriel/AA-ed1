#ifndef DATAINPUT_H_INCLUDED
#define DATAINPUT_H_INCLUDED
#include "node.h"
#include "linkedlist.h"

long totalChar(char*);
LINKEDLIST * createLeafNodes(char*, LINKEDLIST *);
LINKEDLIST* reCreateTable(FILE*);
void compressFILE(char*, char*,LINKEDLIST*);
void writeBinCode(FILE*);
void fileTotalBits(LINKEDLIST *, char*);
void uncompressFILE(char *);
int* transformaBinario(FILE *, long);
void copyBinCodes(FILE* ,LINKEDLIST *);
#endif
