
#include <stdio.h>
#include "binarytree.h"
#include <stdlib.h>
#include "node.h"
#include "heap.h"
#include "linkedlist.h"
#include "node.h"

#define TAM 500

typedef struct{
	NODE* raiz;
	char cod[TAM][TAM];
}HUFF_TREE;

void criaHuff_tree(LINKEDLIST* lista){
	
	//HUFF_TREE* arv = (HUFF_TREE*)malloc(sizeof(HUFF_TREE));
	
	/*
	LINKEDLIST_NODE* chars = (LINKEDLIST_NODE*)malloc(sizeof(LINKEDLIST_NODE*));
	NODE_LIST* no = (NODE_LIST*)malloc(sizeof(NODE_LIST));
	chars->first=no;
	CHARS->ende=no;
	chars->size=1;
	aux->data = NULL;
	
	char data;
    data = fgetc(input);
    no->data = data;
    no->frequency=1;
	
	while(1){
        data = fgetc(input);
		if(data == EOF)
			break;
			
		for(i=0;i<chars->size;i++){
			if(data == no->data){
			   no->frequency++;
			   no=chars->first;
			   break;
			 }
			else if(no == chars->end){
				NODE_LIST* novo = (NODE_LIST*)malloc(sizeof(NODE_LIST));
				novo->ant = no;
				novo->data = data;
				chars->end = novo;
				no=chars->first;
				break;
			}
			else
			   no=no->prox;
			   
		}
		
	}
*/
	BINARY_TREE* arv =(BINARY_TREE*)malloc(sizeof(BINARY_TREE));
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP));

/*	for(i=0;i<chars->size;i++){
        NODE* temp = (NODE*)malloc(sizeof(NODE));
        temp->data = no->data;
        temp->frequency =  no->frequency;
        heap_push(heap,temp);

	}


*/	
	NODE* noTemp = (NODE *)malloc(sizeof(NODE));
	CELL* cellTemp = (CELL*)malloc(sizeof(CELL));
	for(i=0;i<lista->size;i++){
        
        cellTemp = removeFirst(lista);
        noTemp = cellTemp->leaf;
        heap_push(heap,noTemp);
}
	while( heap->end > 1){
	     
	     NODE* fesq = heap_pop(heap);
	     NODE* fdir = heap_pop(heap);
	     
	     NODE *novo = (NODE *)malloc(sizeof(NODE));
	     
	     novo->data = NULL;
	     novo->frequency = fesq->frequency + fdir->frequency;
	     novo->leftChild = fesq;
	     novo->rightChild = fdir;
	     
	     heap_push(heap,novo);
	
	
	}
	
	arv->root = heap_pop(heap);
	
	
}