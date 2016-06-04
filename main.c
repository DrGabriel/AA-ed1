#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "heap.h"
#include "datainput.h"
#include "linkedlist.h"
#include "string.h"

int main(int argc, char *argv[]){

	//transformaBinario(output);
	int i;
	
	LINKEDLIST *list1 = new_list();
	CELL * paux;
	list1 =codeTable(list1);
	compressFILE(argv[1],agrv[2],list1);
	free(list1);

	return 0;
}