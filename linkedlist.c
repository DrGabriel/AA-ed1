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

void insertList(NODE* leaf,CHARBINCODE* binCode,LINKEDLIST *list){
	CELL *cell;
	if(binCode == NULL)
		cell = new_cell(leaf,NULL);
	else
		cell = new_cell(NULL,binCode);


	if(list->first == NULL){
		list->first = cell;		
	}else{
		list->end->next = cell;
	}
	list->size++;
	list->end = cell;
}

CELL *new_cell(NODE *node,CHARBINCODE * binCode){
	CELL *cell = (CELL*) malloc(sizeof(CELL));
	if(cell !=NULL){
		if(binCode == NULL){
			cell->leaf = node;
			cell->binCode = NULL;
			cell->next = NULL;
		}else{
			cell->leaf = NULL;
			cell->binCode = binCode;
			cell->next = NULL;
		}

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

LINKEDLIST *codeTable(LINKEDLIST *list){
	CHARBINCODE * paux1 = new_binCode('a',"0011");
	insertList(NULL,paux1,list);
	paux1 = new_binCode('b',"011011");
	insertList(NULL,paux1,list);
	paux1 = new_binCode('c',"11111");
	insertList(NULL,paux1,list);
	paux1 = new_binCode('d',"00100");
	insertList(NULL,paux1,list);
	paux1 = new_binCode('e',"101");
	insertList(NULL,paux1,list);

	return list;
}

CHARBINCODE *new_binCode(char character, char* code){
	CHARBINCODE * binCode = (CHARBINCODE*) malloc(sizeof(CHARBINCODE));
	if(binCode != NULL){
		binCode->character = character;
		binCode->bincode = code;
	}else{
		printf("No memory available for new binary code with char\n");
	}
	return binCode;
}

char * searchCode(char data, LINKEDLIST * codeTable){
	CELL *paux = codeTable->first;
	while(paux != NULL){
		if(paux->binCode->character == data){
			return paux->binCode->bincode;
		}
		paux = paux->next;
	}
	printf("CHAR NOT FOUND: %c DEC CODE: %d\n",data,data);
	return NULL;
}