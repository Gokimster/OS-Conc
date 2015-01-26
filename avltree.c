#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

struct AVLTREE {
  int key;
  int value;
  int height;
  avltree *left;
  avltree *right;
} ;

/*------------------------------------------------------------------
 * TO DO BE DOOOO BEEEE DOO                                         |
 *------------------------------------------------------------------
 * balance factor function for the avl. bf <=1                      |
 * keep the height of the tree in  a var                            |
 * left rotation                                                    |
 * right rotation                                                   |
 * mebbeh a function to get the bigger number, just for convenience |
 *------------------------------------------------------------------
 */


avltree *mkNode( int key, int value, avltree *left, avltree *right)
{
  avltree *avlt =(avltree*) malloc(sizeof(avltree));
  avlt->key = key;
  avlt->value = value;
  avlt->height = height;
  avlt->left = left;
  avlt->right = right;

  return avlt;
}

avltree *freeNode( avltree * tree)
{
  avltree *temp = mergeAvlTrees(tree->left, tree->right);
  free(tree);
  return temp;
}

avltree *freeAvlTree( avltree *tree)
{
  if (tree->left != NULL)
  {
    freeAvlTree(tree->left);
    tree->left = NULL;
  }
  if (tree->right != NULL)
  {
    freeAvlTree(tree->right);
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


int getBigger(int x, int y){
  if(x>y) return x; else return y;
}



void printAvlTree( avltree *tree)
{
  printAvlTreeOff( 0, tree);
}

//prioritising tree2 - if a kew appears in both trees, it will keep the one in the second tree
avltree *mergeAvlTrees( avltree *tree1, avltree *tree2)
{
  avltree *avlt =(avltree*) malloc(sizeof(avltree));
  avlt = tree1;
  if(tree2 == NULL)
    return avlt;
  else
  {
    insertKey(tree2->key, tree2->value, avlt);
    avlt = mergeAvlTrees(avlt, tree2->left);
    avlt = mergeAvlTrees(avlt, tree2->right);
  }
}

/*a function to do the left rotation of the tree 
 *it helps handling the case of an unbalanced tree
 * used in case the right side of the tree has a height 
 * difference with the left side more than 1. (i.e. balance factor of this node is more than 1)
 */
 avltree *rotateLeft(avltree *avlt)
{
    avltree *right = avlt->right;
    avltree *leftOfRight = right->left;
 
    // rotate
    right->left = avlt;
    avlt->right = leftOfRight;
 
    //  fix heights of thier new poistions
    avlt->height = getBigger(avlt->left->height, avlt->right->height)+1;
    right->height = getBigger(right->left->height, right->right->height)+1;
 
    //  new tree
    return right;
}

avltree *rotateRight(avltree *avlt){
  avltree *left = avlt->left;
  avltree *rightOfLeft = left->right;
 
    // rotate
    left->right = avlt;
    avlt->left = rightOfLeft;
 
    // fix heights with nwe positions
    avlt->height = getBigger(avlt->left->height, avlt->right->height)+1;
    left->height = getBigger(left->left->height, left->right->height)+1;
 
    //new tree
    return left;
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
  avltree *avlt =(avltree*) malloc(sizeof(avltree));
   avlt=tree;
  int found = findKey(key, tree);
  if(found==0)
  {
    printf("Could not find the key. \n");
    return NULL;

  }else if(avlt->left!=NULL && avlt->left->key == key){
    
    avlt->left=mergeAvlTrees(avlt->left->left, avlt->left->right);
    return avlt;
 
  }else if(avlt->right!=NULL && avlt->right->key == key){
     
    avlt->right=mergeAvlTrees(avlt->right->left, avlt->right->right);
     return avlt;
  }else if(avlt->key==key){
    avlt = mergeAvlTrees(avlt->left, avlt->right); 
   return avlt;
  }
  else 
  {
    if(key > avlt->key && avlt->right!=NULL)
    {
     deleteKey(key,avlt->right);
     return avlt;
    }else if(key < avlt->key){
    deleteKey(key,avlt->left);
     return avlt;
    }
    
  }

  avlt->height = max(height(avlt->left), height(avlt->right)) + 1;
  int balance = getBalance(avlt);
  if (balance > 1 && getBalance(avlt->left) >= 0)
    return rightRotate(avlt);

  if (balance > 1 && getBalance(avlt->left) < 0)
  {
    avlt->left =  leftRotate(avlt->left);
    return rightRotate(avlt);
  }

  if (balance < -1 && getBalance(avlt->right) <= 0)
    return leftRotate(avlt);

  if (balance < -1 && getBalance(avlt->right) > 0)
  {
    avlt->right = rightRotate(avlt->right);
    return leftRotate(avlt);
  }

  return avlt;
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

