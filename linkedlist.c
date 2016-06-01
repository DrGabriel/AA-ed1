#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"


NODE * searchData(char data,LINKEDLIST * list){
	CELL * paux = list->first;
	while(paux != NULL){
		if(paux->leaf->data == data)
			return paux->leaf;
		paux = paux->next;
	}
	return NULL;
}

void insertList(NODE* leaf,LINKEDLIST *list){
	CELL *cell = new_cell(leaf);

	if(list->first == NULL){
		list->first = cell;		
	}else{
		list->end->next = cell;
	}
	list->size++;
	list->end = cell;
}

CELL *new_cell(NODE *node){
	CELL *cell = (CELL*) malloc(sizeof(CELL));
	if(cell !=NULL){
		cell->leaf = node;
		cell->next = NULL;
	}else{
		printf("No memory available for new cell\n");
	}

	return cell;
}

LINKEDLIST * new_list(){
	LINKEDLIST *list = (LINKEDLIST*) malloc(sizeof(LINKEDLIST));
	if(list != NULL){
		list->first = NULL;
		list->end = NULL;
		list->size =0;
	}else{
		printf("No memory available for new cell\n");
	}
	return list;
}

CELL *removeFirst(LINKEDLIST *list){
	CELL *paux;
	if(!emptyList(list)){
		paux = list->first;
		list->first = list->first->next;
		list->size--;
	}else{
		printf("Linked list is empty, remove failed\n");
	}
	return paux;
}

int emptyList(LINKEDLIST *list){
	return (list->size == 0);
}