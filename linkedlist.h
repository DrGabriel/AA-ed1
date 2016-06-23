#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include "node.h"

typedef struct CHARBINCODE{
	char character;
	char * bincode;
}CHARBINCODE;

typedef struct CELL{
	struct CELL *next;
	NODE *leaf;
	CHARBINCODE * binCode;
}CELL;

typedef struct LINKEDLIST{
	CELL *first;
	CELL *end;
	int size;
}LINKEDLIST;

NODE* searchData(char,LINKEDLIST *);
void insertList(NODE*,CHARBINCODE*,LINKEDLIST *);
CELL *new_cell(NODE *,CHARBINCODE *);
CELL *removeFirst(LINKEDLIST *);
LINKEDLIST * new_list();
int emptyList(LINKEDLIST *);
CHARBINCODE *new_binCode(char,char*);
char * searchCode(char, LINKEDLIST *);
char searchBinCode(int,int *,LINKEDLIST *);

#endif