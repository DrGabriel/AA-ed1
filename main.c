#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "heap.h"
#include "datainput.h"
#include "linkedlist.h"
#include "string.h"
#include "huff_tree.h"


int main(int argc, char *argv[]){

	if(argc == 3){
		LINKEDLIST *list1 = new_list(); 
		LINKEDLIST *list2 = new_list();
		list2 = createLeafNodes(argv[1],list2);
		list1 = criaHuff_tree(list2);
		compressFILE(argv[1],argv[2],list1);
		free(list1);
		free(list2);
	}else{
		uncompressFILE(argv[1]);
	}


	return 0;
}