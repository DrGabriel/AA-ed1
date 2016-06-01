#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include "node.h"

typedef struct BINARY_TREE{
	NODE *root;
	NODE *last;
}BINARY_TREE;

BINARY_TREE *new_tree(char);
//void insert(char,BINARY_TREE*);
//void destroy_tree(BINARY_TREE**);
#endif