#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "heap.h"
#include "datainput.h"
#include "linkedlist.h"
#include "string.h"

int main(int argc, char *argv[]){
	FILE *input = fopen(argv[1],"r");

	FILE *output;
	int i;
	/*while(1){
		char c = fgetc(input);
		if(c == EOF)
			break;
		printf("%c\n", c);

	}*/
	LINKEDLIST *list1 = new_list();
	CELL * paux;
	list1 =codeTable(list1);
	compressFILE(input,list1,output);
	free(list1);

	return 0;
}