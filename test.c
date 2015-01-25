#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

void main()
{
  bintree *tree;

  tree = mkNode(6,6,mkNode(5,5,NULL,NULL),(mkNode(7,7,NULL,NULL)));

 //printBinTree(tree);
  
  }