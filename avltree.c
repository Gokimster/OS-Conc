#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

struct AVLTREE {
  int key;
  int value;
  avltree *left;
  avltree *right;
} ;

avltree *mkNode( int key, int value, avltree *left, avltree *right)
{
  avltree *bt =(avltree*) malloc(sizeof(avltree));
  bt->key = key;
  bt->value = value;
  bt->left = left;
  bt->right = right;
  return bt;
}

void freeNode( avltree * tree)
{
  
}

void freeAvlTree( avltree *tree)
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
void printAvlTreeOff( int off, avltree *tree)
{
  if (tree != NULL) {
    printf( "Node{ key:%d value:%d\n", tree->key, tree->value);
    off += 6;
    indent( off);
    printf( "left: ");
    printAvlTreeOff( off+6, tree->left);
    indent( off);
    printf( "right:");
    printAvlTreeOff( off+6, tree->right);
    indent( off-2);
    printf( "}\n");
  } else {
    printf( "NULL\n");
  }
}

void printAvlTree( avltree *tree)
{
  printAvlTreeOff( 0, tree);
}

//prioritising tree2 - if a kew appears in both trees, it will keep the one in the second tree
avltree *mergeAvlTrees( avltree *tree1, avltree *tree2)
{
  avltree *bt =(avltree*) malloc(sizeof(avltree));
  bt = tree1;
  if(tree2 == NULL)
    return bt;
  else
  {
    insertKey(tree2->key, tree2->value, bt);
    bt = mergeAvlTrees(bt, tree2->left);
    bt = mergeAvlTrees(bt, tree2->right);
  }
}

avltree *insertKey( int key, int value, avltree *tree)
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
        avltree *newNode = (avltree*)malloc(sizeof(avltree));
        newNode->key =key;
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        tree->left = newNode;
        return;
    }
    else if(tree->right == NULL  && key > tree->key) {
        avltree *newtree = (avltree*)malloc(sizeof(avltree));
        newtree->key = key;
        newtree->value = value;
        newtree->left = NULL;
        newtree->right = NULL;
        tree->right = newtree;
        return;
    }
}


avltree *deleteKey( int key, avltree *tree)
{
  /* fill in here */
}

int findKey( int key, avltree *tree)
{
  if(tree == NULL)
  {
    printf("Could not find the key. \n");
    return 0;
  }
  if (tree->key == key)
  {
    printf("The value for the key is  %d \n", tree->value);
  }
  else 
  {
    if(key > tree->key)
    {
      findKey(key, tree->right);
    }else
    {
      findKey(key, tree->left);
    }
  }
}

