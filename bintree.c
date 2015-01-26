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

bintree *freeNode( bintree * tree)
{
  bintree *temp = mergeBinTrees(tree->left, tree->right);
  free(tree);
  return temp;
}

bintree *freeBinTree( bintree *tree)
{
  if (tree->left != NULL)
  {
    freeBinTree(tree->left);
    tree->left = NULL;
  }
  if (tree->right != NULL)
  {
    freeBinTree(tree->right);
    tree->right = NULL;
  }

  return freeNode(tree);
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

//prioritising tree2 - if a new appears in both trees, it will keep the one in the second tree
bintree *mergeBinTrees( bintree *tree1, bintree *tree2)
{
  bintree *bt =(bintree*) malloc(sizeof(bintree));
  bt = tree1;
  if(tree2 == NULL)
    return bt;
  else
  {
    insertKey(tree2->key, tree2->value, bt);
    bt = mergeBinTrees(bt, tree2->left);
    bt = mergeBinTrees(bt, tree2->right);
  }
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
   bintree *bt =(bintree*) malloc(sizeof(bintree));
   bt=tree;
  int found = findKey(key, tree);
  if(found==0)
  {
    printf("Could not find the key. \n");
    return NULL;

  }else if(bt->left!=NULL && bt->left->key == key){
    
    bt->left=mergeBinTrees(bt->left->left, bt->left->right);
    return bt;
 
  }else if(bt->right!=NULL && bt->right->key == key){
     
    bt->right=mergeBinTrees(bt->right->left, bt->right->right);
     return bt;
  }else if(bt->key==key){
  bt = mergeBinTrees(bt->left, bt->right); 
   return bt;
  }
  else 
  {
    if(key > bt->key && bt->right!=NULL)
    {
     deleteKey(key,bt->right);
     return bt;
    }else if(key < bt->key){
    deleteKey(key,bt->left);
     return bt;
    }
    
  }
}

int findKey( int key, bintree *tree)
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

