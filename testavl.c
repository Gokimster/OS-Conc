#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

void main()
{
  avltree *tree;
  avltree *tree1;
  avltree *tree2;
  tree1 = mkNode(5,5,NULL,NULL);


  printAvlTree(tree1);
  
  tree1 = insertKey(6,6, tree1);
  tree1 = insertKey(4,4, tree1);
  tree1 = insertKey(7,7, tree1);
  tree1 = insertKey(8,8, tree1);
  tree1 = insertKey(9,9, tree1);
  printf("-------------------------------------------\n");
  printf("Inserting Done\n");
  printf("-------------------------------------------\n");
  printAvlTree(tree1);
  printf("-------------------------------------------\n");
  printf("Removing key 4\n");
  printf("-------------------------------------------\n");
  printAvlTree(deleteKey(4,tree1));
    
  printf("-------------------------------------------\n");
  printf("Free node \n");
  printf("-------------------------------------------\n");

  tree = freeNode(tree1);
  printf("Freed\n");
  printAvlTree(tree);

  printf("-------------------------------------------\n");
  printf("Free node \n");
  printf("-------------------------------------------\n");
  tree1 = mkNode(5,5,NULL,NULL);

  tree = freeNode(tree1);
  printAvlTree(tree);

  printf("-------------------------------------------\n");
  printf("Free tree \n");
  printf("-------------------------------------------\n");
  tree1 = mkNode(5,5,NULL,NULL);
  tree1 = insertKey(6,6, tree1);
  tree1 = insertKey(4,4, tree1);
  tree1 = insertKey(7,7, tree1);
  tree1 = insertKey(3,3, tree1);
  tree1 = insertKey(1,1, tree1);
  printAvlTree(tree1);
  printf("-------------------------------------------\n");
  printf("Freed\n");
  printf("-------------------------------------------\n");
  tree = freeAvlTree(tree1);
  printAvlTree(tree);
  }