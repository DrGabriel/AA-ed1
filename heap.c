#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


HEAP *new_heap(int size){
	HEAP *heap = (HEAP*) malloc(sizeof(HEAP));
	heap->nodes = malloc(sizeof(NODE*) * size);
	if(heap != NULL && heap->nodes !=NULL){
		heap->end = -1;

	}else{
		printf("No memory available for new heap\n");
	}
	return heap;
}

int empty_heap(HEAP *heap){
	return (heap->end == -1);
}

void swap(HEAP * heap, int actual, int new_pos){
	NODE *tmp = heap->nodes[actual];
	heap->nodes[actual] = heap->nodes[new_pos];
	heap->nodes[new_pos] = tmp;
}
void perc_up(HEAP *heap){
	int pos = heap->end;
	int dad = (pos - 1)/2;
	while(pos > 0 && heap->nodes[pos]->frequency < heap->nodes[dad]->frequency){
		swap(heap,pos,dad);
		pos = dad;
		dad = (dad -1)/2;
	}
}

void perc_down(HEAP *heap){
	int pos = 0;
	int smallestChild;
	while(pos <= heap->end/2){
		int leftChild  = 2 * pos + 1;
		int rightChild = 2 * pos + 1;

		if(rightChild <= heap->end && 
			heap->nodes[leftChild]->frequency > heap->nodes[rightChild]->frequency){
			smallestChild = rightChild;
		}else{
			smallestChild = leftChild;
		}

		if(heap->nodes[pos]->frequency <= heap->nodes[smallestChild]->frequency){
			break;
		}

		swap(heap,pos,smallestChild);
		pos = smallestChild;
	}
}

void heap_push(HEAP *heap, NODE *node){
	heap->end++;
	heap->nodes[heap->end] = node;
	perc_up(heap);
}

NODE *heap_pop(HEAP *heap){
	if(!empty_heap(heap)){
		NODE *node = heap->nodes[0];
		heap->nodes[0] = heap->nodes[heap->end];
		heap->end--;
		if(!empty_heap(heap))
		perc_down(heap);
		return node;
	}else{
		printf("Heap is empty\n");
	}

	return NULL;
}

void printHeap(HEAP * heap){
	int i;
	for(i=0; i<= heap->end;i++){
		printf("%d ",heap->nodes[i]->frequency);
	}
	printf("\n");
}

