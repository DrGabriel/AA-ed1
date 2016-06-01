#include <stdio.h>
#include <stdlib.h>
#include "datainput.h"


long totalChar(FILE * file){
	long totalChar = 0;
	char c;

	while(1){
		c = getc(file);
		if(c == EOF)
			break;
		totalChar++;
	}

	return totalChar;
}

LINKEDLIST * createLeafNodes(FILE *file, LINKEDLIST *list){
	NODE *paux;
	char data;

	while(1){
		data = getc(file);
		if(data == EOF)
			break;
		paux = searchData(data,list);
		if(paux == NULL){
			paux = new_node(data);
			insertList(paux,list);
		}else{
			paux->frequency++;
		}
	}
	return list;

}