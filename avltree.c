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
  avltree *bt =(avltree*) malloc(sizeof(avltree));
  bt->key = key;
  bt->value = value;
  bt->height = height;
  bt->left = left;
  bt->right = right;

  return bt;
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


int getBigger(int a, int b){
  if(a>b) return a; else return b;
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

/*a function to do the left rotation of the tree 
 *it helps handling the case of an unbalanced tree
 * used in case the right side of the tree has a height 
 * difference with the left side more than 1. (i.e. balance factor of this node is more than 1)
 */
 avltree *rotateLeft(bintree *bt)
{
    avltree *right = bt->right;
    avltree *leftOfRight = right->left;
 
    // rotate
    right->left = bt;
    bt->right = leftOfRight;
 
    //  fix heights of thier new poistions
    bt->height = getBigger(bt->left->height, bt->right->height)+1;
    right->height = getBigger(right->left->height, right->right->height)+1;
 
    //  new tree
    return right;
}

avltree *rotateRight(bintree *bt){
  avltree *left = bt->left;
  avltree *rightOfLeft = left->right;
 
    // rotate
    left->right = bt;
    bt->left = rightOfLeft;
 
    // fix heights with nwe positions
    bt->height = getBigger(bt->left->height, bt->right->height)+1;
    left->height = getBigger(left->left->height, left->right->height)+1;
 
    //new tree
    return left;
}


int getHeight(avltree *tree){
  if(tree==NULL){
    return 0;
  }else return tree->height;
}
 
// Get Balance factor of node N
int getBalance(avltree *bt)
{
    if (bt == NULL)
        return 0;
    return getHeight(bt->left) - getHeight(bt->right);
}
 
avltree insert(int key,int value, avltree *tree)
{
    /* 1.  Perform the normal BST rotation */
   avltree *bt =(avltree*) malloc(sizeof(avltree));
    bt=tree;
    if( bt->key > key && bt->left != NULL) {
        bt = bt->left;
        insertKey(key,value,bt);
        //return bt;
    }
    else if(bt->key < key && bt->right != NULL) {
        bt = bt->right;
        insertKey(key,value, bt);
       // return bt;
    }
    else if (bt->key == key){
      bt->value = value;
    }
    else if(bt->left == NULL && key < bt->key) {
        bintree *newNode = mkNode(key, value, NULL, NULL);
        bt->left = newNode;
        //return bt;
        
    }
    else if(tree->right == NULL  && key > tree->key) {
        bintree *newNode = mkNode(key, value, NULL, NULL);
        bt->right = newNode;
        
        //return bt;
        
    }
    /* 2. Update height of this ancestor node */
    bt->height = getHeight(bt->left), getHeight(bt->right)) + 1;
 
    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(bt);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < bt->left->key)
        return rotateRight(bt);
 
    // Right Right Case
    if (balance < -1 && key > bt->right->key)
        return rotateLeft(bt);
 
    // Left Right Case
    if (balance > 1 && key > bt->left->key)
    {
        node->left =  rotateLeft(bt->left);
        return rotateRight(bt);
    }
 
    // Right Left Case
    if (balance < -1 && key < bt->right->key)
    {
        node->right = rotateRight(bt->right);
        return rotateLeft(bt);
    }
 
    /* return the (unchanged) node pointer */
    return bt;
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

