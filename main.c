#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "heap.h"
#include "datainput.h"
#include "linkedlist.h"
#include "string.h"
#include "huff_tree.h"


int main(int argc, char *argv[]){

	//transformaBinario(output);
	int i;
	
	//FILE* entrada = fopen(argv[1],"r");
	
	LINKEDLIST *list1 = new_list();
	//CELL * paux;
	//list1 = codeTable(list1);
	list1 = criaHuff_tree(createLeafNodes(argv[1],list1));
    
    CELL* teste = list1->first;
    
    for(i=0;i<list1->size;i++){
	   printf("%c\n", teste->leaf->data);
	   teste = teste->next;	
	}
            
	compressFILE(argv[1],argv[2],list1);
	free(list1);

	return 0;
}
