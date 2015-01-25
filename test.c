#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"


void main()
{
  bintree *tree;

  tree = mkNode( 5, 5,
                 mkNode( 3, 3,
                         mkNode( 1, 1,
                                 NULL,
                                 mkNode( 4, 4, NULL, NULL)),
                         NULL),
                 NULL);

  printBinTreeoff(3, tree);
  }