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
  bintree *bt =(bintree*) malloc(sizeof(bintree));
  bt->key = key;
  bt->value = value;
  bt->left = left;
  bt->right = right;
  return bt;
}

void freeNode( bintree * tree)
{
  
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
    if( tree->key > key && tree->left != NULL) {
        tree = tree->left;
        insertKey(key,value,tree);
    }
    else if(tree->key < key && tree->right != NULL) {
        tree = tree->right;
        insertKey(key,value, tree);
    }
    else if (tree->key == key){
      tree->value = value;
    }
    else if(tree->left == NULL && key < tree->key) {
        bintree *newNode = (bintree*)malloc(sizeof(bintree));
        newNode->key =key;
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        tree->left = newNode;
        return;
    }
    else if(tree->right == NULL  && key > tree->key) {
        bintree *newtree = (bintree*)malloc(sizeof(bintree));
        newtree->key = key;
        newtree->value = value;
        newtree->left = NULL;
        newtree->right = NULL;
        tree->right = newtree;
        return;
    }
}


bintree *deleteKey( int key, bintree *tree)
{
  /* fill in here */
}

int findKey( int key, bintree *tree)
{
  /* fill in here */
}

