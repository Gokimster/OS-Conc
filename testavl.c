#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

void main()
{
 // avltree *tree;
  avltree *tree1;
 // avltree *tree2;
  tree1 = mkNode(5,5,NULL,NULL);
 // tree2 = mkNode(7,7,NULL,NULL);
  //tree = mkNode(6,6, tree1, tree2);


  printAvlTree(tree1);
  printf(",Inserting key six, value six\n");
  insertKey(6,6, tree1);
  printAvlTree(tree1);
  printf("Inserting key four value four\n");
  insertKey(4,4, tree1);
  printAvlTree(tree1);
  findKey(4, tree1);
  findKey(10, tree1);

  avltree *tree;
  avltree *treeP;
  avltree *tree2;
  tree1 = mkNode(2,2,NULL,NULL);
  tree2 = mkNode(9,9,NULL,NULL);
  tree = mkNode(3,3, tree1, tree2);
  tree1 = mkNode(4,4,NULL,NULL);
  tree2 = mkNode(7,7,NULL,NULL);
  treeP = mkNode(1,1, tree1, tree2);
  tree1 = mergeAvlTrees(tree, treeP);
  printf("Merging Trees\n");
  printAvlTree(tree1);
  
  }