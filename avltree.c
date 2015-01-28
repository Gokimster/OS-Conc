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
  avlt->height = 1;
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
    avlt = insertKey(tree2->key, tree2->value, avlt);
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
    avlt->height = (getBigger(getHeight(avlt->left), getHeight(avlt->right)))+1;
    right->height = (getBigger(getHeight(right->left), getHeight(right->right)))+1;
 
    //  new tree
    return right;
}

avltree *rotateRight( avltree *avlt){
  avltree *left = avlt->left;
  avltree *rightOfLeft = left->right;
 
    // rotate
    left->right = avlt;
    avlt->left = rightOfLeft;
 
    // fix heights with nwe positions
    avlt->height = (getBigger(getHeight(avlt->left), getHeight(avlt->right)))+1;
    left->height = (getBigger(getHeight(left->left), getHeight(left->right)))+1;
 
    //new tree
    return left;
}


int getHeight(avltree *tree){
  if(tree==NULL){
    return 0;
  }else return tree->height;
}

int getBalance(avltree *avlt)
{
    if (avlt == NULL)
        return 0;
    return getHeight(avlt->left) - getHeight(avlt->right);
}
 
avltree *insertKey(int key,int value, avltree *tree)
{
   
    avltree *avlt =(avltree*) malloc(sizeof(avltree));
    avlt=tree;

    if (avlt == NULL)
        return(mkNode(key,value, NULL, NULL));

    if( avlt->key > key && avlt->left != NULL) {
        avlt->left = insertKey(key,value,avlt->left);
        
    }
    else if(avlt->key < key && avlt->right != NULL) {
        avlt-> right = insertKey(key,value, avlt->right);
    }
    else if (avlt->key == key){
      avlt->value = value;
    }
    else if(avlt->left == NULL && key < avlt->key) {
        avltree *newNode = mkNode(key, value, NULL, NULL);
        avlt->left = newNode;
    }
    else if(tree->right == NULL  && key > tree->key) {
        avltree *newNode = mkNode(key, value, NULL, NULL);
        avlt->right = newNode;
    }
    avlt = rebalance(avlt,key);
    return avlt;
   

}

avltree *rebalance(avltree *avltree, int key){
  avltree->height = (getBigger(getHeight(avltree->left), getHeight(avltree->right))) + 1;
  int balance = getBalance(avltree);
 
    // If this avlt becomes unbalanced, then there are 4 cases
    // Left Left 
    if (balance > 1 && key < avltree->left->key)
        return rotateRight(avltree);
 
    // Right Right Case
    if (balance < -1 && key > avltree->right->key)
        return rotateLeft(avltree);
 
    // Left Right Case
    if (balance > 1 && key > avltree->left->key)
    {
        avltree->left =  rotateLeft(avltree->left);
        return rotateRight(avltree);
    }
 
    // Right Left Case
    if (balance < -1 && key < avltree->right->key)
    {
        avltree->right = rotateRight(avltree->right);
        return rotateLeft(avltree);
    }
    else return avltree;
 
    /* return it unchanged */
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
    rebalance(avlt,key);
    return avlt;
 
  }else if(avlt->right!=NULL && avlt->right->key == key){
     
    avlt->right=mergeAvlTrees(avlt->right->left, avlt->right->right);
    rebalance(avlt,key);
     return avlt;
  }else if(avlt->key==key){
    avlt = mergeAvlTrees(avlt->left, avlt->right); 
    rebalance(avlt,key);
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

