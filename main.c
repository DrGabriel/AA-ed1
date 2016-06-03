#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "heap.h"
#include "datainput.h"
#include "linkedlist.h"
#include "string.h"

int main(int argc, char *argv[]){
	FILE *input = fopen(argv[1],"r");

	FILE *output = fopen(argv[2],"w");;
	int i;
	
	LINKEDLIST *list1 = new_list();
	CELL * paux;
	list1 =codeTable(list1);
	compressFILE(input,list1,output);
	free(list1);

	return 0;
}