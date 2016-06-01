#include <stdio.h>
#include <stdlib.h>
#include "node.h"

NODE *new_node(char data){
	NODE *node = (NODE *) malloc(sizeof(NODE));
	if(node != NULL){
		node->leftChild = NULL;
		node->rightChild = NULL;
		node->data = data;
		node->frequency = 1;
	}else{
		printf("No memory available for new node\n");
	}
	return node;
}