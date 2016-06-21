#ifndef DATAINPUT_H_INCLUDED
#define DATAINPUT_H_INCLUDED
#include "node.h"
#include "linkedlist.h"

long totalChar(char*);
LINKEDLIST * createLeafNodes(char*, LINKEDLIST *);
LINKEDLIST* reCreateTable(char*);
void compressFILE(char*, char*,LINKEDLIST*);
void writeBinCode(char,LINKEDLIST *,FILE*);
void fileTotalBits(LINKEDLIST *, char*);
#endif
