#ifndef DATAINPUT_H_INCLUDED
#define DATAINPUT_H_INCLUDED
#include "node.h"
#include "linkedlist.h"

double getTime();
long totalChar(char*);
LINKEDLIST * createLeafNodes(char*, LINKEDLIST *);
void compressFILE(char*, char*,LINKEDLIST*);
void writeBinCode(char,LINKEDLIST *,char*);
void fileTotalBits(LINKEDLIST *, char*);
#endif