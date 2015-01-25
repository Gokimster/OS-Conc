#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

struct BINTREE {
  int key;
  int value;
  bintree *left;
  bintree *right;
} ;

bintree *mkNode( int key, int value, bintree *left, bintree *right)
{
  BINTREE bt;
  bt.key = key;
  bt.value = value;
  bt.left = left;
  bt.right = right;
  return bt
}

static
void printBinTreeOff( int off, bintree *tree)
{
  if (tree != NULL) {
    printf( "Node{ key:%d value:%d\n", tree->key, tree->value);
    off += 6;
    indent( off);
    printf( "left: ");
    printBinTreeOff( off+6, tree->left);
    indent( off);
    printf( "right:");
    printBinTreeOff( off+6, tree->right);
    indent( off-2);
    printf( "}\n");
  } else {
    printf( "NULL\n");
  }
}

int main()
{
  bintree *tree;

  tree = mkNode( 5, 5,
                 mkNode( 3, 3,
                         mkNode( 1, 1,
                                 NULL,
                                 mkNode( 4, 4, NULL, NULL)),
                         NULL),
                 NULL);

  printBinTreeoff(3 tree);
  }