#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "heap.h"
#include "datainput.h"
#include "linkedlist.h"

int main(int argc, char *argv[]){
    FILE *fp = fopen(argv[1], "r"); /* "r" = open for reading */
	LINKEDLIST *list = new_list();
	list = createLeafNodes(fp,list);
	HEAP* heap = new_heap(list->size);
	CELL *paux;
	int i;
	for(i=0;i<=list->size;i++){
		paux = removeFirst(list);
		printf("DATA:%c FREQUENCY:%d\n",paux->leaf->data, paux->leaf->frequency);
		heap_push(heap,paux->leaf);
	}
	printf("HEAP before pop: ");
	printHeap(heap);
	NODE *paux1 = heap_pop(heap);
	printf("HEAP after pop: ");
	printHeap(heap);



	return 0;
}