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
  printf("CREATING tree\n");
  bintree *bt;
  bt->key = key;
  printf("%d\n",bt->key);
  bt->value = value;
  printf("%d\n",bt->value);
  bt->left = left;
  bt->right = right;
  return bt;
}

void freeNode( bintree * tree)
{
  /* fill in here */
}

void freeBinTree( bintree *tree)
{
  /* fill in here */
}

static
void indent( int off)
{
  int i;

  for( i=0; i<off; i++) {
    printf( " ");
  }
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

void printBinTree( bintree *tree)
{
  printBinTreeOff( 0, tree);
}

bintree *mergeBinTrees( bintree *tree1, bintree *tree2)
{
  /* fill in here */
}

bintree *insertKey( int key, int value, bintree *tree)
{
  /* fill in here */
}

bintree *deleteKey( int key, bintree *tree)
{
  /* fill in here */
}

int findKey( int key, bintree *tree)
{
  /* fill in here */
}

