#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

void main()
{
  bintree *tree;
  bintree *tree1;
  bintree *tree2;
  tree1 = mkNode(5,5,NULL,NULL);
  tree2 = mkNode(7,7,NULL,NULL);
  tree = mkNode(6,6, tree1, tree2);

  printBinTree(tree);
  findKey(7, tree);
  
  }