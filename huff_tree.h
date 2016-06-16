#include <stdio.h>
#include "binarytree.h"
#include <stdlib.h>
#include "node.h"
#include "heap.h"
#include "linkedlist.h"
#include "node.h"
#include <string.h>

LINKEDLIST* geraCod(NODE* raiz);
void geraCodAux(NODE* raiz,char* cod,int fimCod,LINKEDLIST* codeList);
LINKEDLIST* criaHuff_tree(LINKEDLIST* lista);
