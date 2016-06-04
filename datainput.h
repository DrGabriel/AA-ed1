#ifndef DATAINPUT_H_INCLUDED
#define DATAINPUT_H_INCLUDED
#include "node.h"
#include "linkedlist.h"

long totalChar(FILE*);
LINKEDLIST * createLeafNodes(FILE *, LINKEDLIST *);
void compressFILE(char*, char*,LINKEDLIST*);
void writeBinCode(char,LINKEDLIST *,FILE *);
void fileTotalBits(LINKEDLIST *, FILE *);
#endif