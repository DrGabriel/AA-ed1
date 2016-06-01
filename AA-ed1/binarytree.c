#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
#include "node.h"

BINARY_TREE *new_tree(char data){
	BINARY_TREE *tree = (BINARY_TREE*) malloc(sizeof(BINARY_TREE));

	if(tree != NULL){
		tree->root = create_node(data);
	}else{
		printf("No memory available for new tree\n");
	}

	return tree;
}