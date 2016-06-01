#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include "node.h"

typedef struct HEAP{
 	NODE **nodes;
 	int end;
}HEAP;

HEAP *new_heap(int);
int empty_heap(HEAP *);
void swap(HEAP *, int, int);
void perc_up(HEAP *);
void perc_down(HEAP *);
void heap_push(HEAP *heap, NODE *node);
void printHeap(HEAP *);
NODE *heap_pop(HEAP *heap);



#endif