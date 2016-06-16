
#include <stdio.h>
#include "binarytree.h"
#include <stdlib.h>
#include "node.h"
#include "heap.h"
#include "linkedlist.h"
#include "node.h"
#include <string.h>

#define TAM 500

typedef struct{
	NODE* raiz;
	char cod[TAM][TAM];
}HUFF_TREE;

void geraCodAux(NODE* raiz,char* cod,int fimCod,LINKEDLIST* codeList);

LINKEDLIST* geraCod(NODE* raiz){
    
    int i;
    char* cod = (char*)malloc(sizeof(char)*2);
	int fimCod =0;
    LINKEDLIST* codes = new_list();
    geraCodAux(raiz,cod,fimCod,codes);
    
    CELL* teste = codes->first;
    for(i=0;i<codes->size;i++){
	   printf("%c\n", teste->leaf->data);
	   teste = teste->next;	
	}
    
    return codes;
    
}

void geraCodAux(NODE* raiz,char* cod,int fimCod,LINKEDLIST* codeList){
		
	   int i;
	   if(raiz != NULL) {
		   cod[fimCod]='0';
		   fimCod++;
		   char* copia =(char*)malloc(sizeof(char)*(fimCod+2));
		   for(i=0;i<fimCod;i++)
		      copia[i]=cod[i];
		        
           geraCodAux(raiz->leftChild,copia,fimCod,codeList);
           
           fimCod--;
           
           cod[fimCod]='1';
           fimCod++;
           for(i=0;i<fimCod;i++)
		      copia[i]=cod[i];
   
           geraCodAux(raiz->rightChild,copia,fimCod,codeList);
           
           if((raiz->leftChild == NULL) && (raiz->rightChild == NULL)){
			   cod[fimCod-1] = '\0';
			   CHARBINCODE* bincode = new_binCode(raiz->data,cod);
               insertList(NULL,bincode,codeList);
               puts(cod);
          }
          //free(copia);
       }
   
}
LINKEDLIST* criaHuff_tree(LINKEDLIST* lista){
	
	
	//BINARY_TREE* arv =(BINARY_TREE*)malloc(sizeof(BINARY_TREE));
	HEAP* heap = new_heap(lista->size);
	
	NODE* noTemp = (NODE *)malloc(sizeof(NODE));
	CELL* cellTemp = (CELL*)malloc(sizeof(CELL));
	
	while(lista->size>0){
        
        cellTemp = removeFirst(lista);
        noTemp = cellTemp->leaf;
        heap_push(heap,noTemp);
        
    }
    
    printHeap(heap);
    
	while( heap->end > 0){
	     
	     NODE* fesq = heap_pop(heap);
	     NODE* fdir = heap_pop(heap);

	     NODE *novo = (NODE *)malloc(sizeof(NODE));
	     
	     novo->data = '#';
	     novo->frequency = fesq->frequency + fdir->frequency;
	     novo->leftChild = fesq;
	     novo->rightChild = fdir;
	     
	     heap_push(heap,novo);
	
	
	}
	
	//NODE* teste = heap_pop(heap);
	
	
	//arv->root = heap_pop(heap);
	
	LINKEDLIST* table = geraCod(heap_pop(heap));
	
	
	

	
	return table;
	
	
	
}
