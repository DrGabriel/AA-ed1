#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>


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

char searchBinCode(int tam,int *code,LINKEDLIST * codeTable){
	CELL * paux = codeTable->first;
	char * copia = malloc(tam * sizeof *copia);
	int i,j=0;
	for(i=0;i<tam;i++){
		if(code[i] == 1)
			copia[i] = '1';
		else
			copia[i] = '0';

	}
	while(paux!=NULL){
		for(i=0;i<strlen(paux->binCode->bincode);i++){
			if(paux->binCode->bincode[i]==copia[i])
				j++;//Se os caracteres forem iguais incrementa j
		}
		if(j== strlen(paux->binCode->bincode))
			return paux->binCode->character; //Se encontrou o codigo retorna
		else
			j=0; //Senão zera o contador

		paux = paux->next;//Vai para o proximo codigo da lista encadeada
	}
	free(copia);

	return '\0';//Nao encontrou o codigo
}