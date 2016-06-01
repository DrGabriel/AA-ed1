#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include "node.h"

typedef struct CELL{
	struct CELL *next;
	NODE *leaf; 
}CELL;
typedef struct LINKEDLIST{
	CELL *first;
	CELL *end;
	int size;
}LINKEDLIST;

NODE* searchData(char,LINKEDLIST *);
void insertList(NODE*,LINKEDLIST *);
CELL *new_cell(NODE *);
CELL *removeFirst(LINKEDLIST *);
LINKEDLIST * new_list();
int emptyList(LINKEDLIST *);

#endif