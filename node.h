#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

typedef struct NODE{
	struct NODE *leftChild;
	struct NODE *rightChild;
	char data;
	int frequency;
}NODE;

NODE *new_node(char);

#endif