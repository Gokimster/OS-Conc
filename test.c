#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

void main()
{
  bintree *tree;
  bintree *tree1;
  bintree *tree2;
  tree1 = mkNode(5,5,NULL,NULL);
 // tree2 = mkNode(7,7,NULL,NULL);
  //tree = mkNode(6,6, tree1, tree2);



  
  insertKey(6,6, tree1);
  insertKey(4,4, tree1);
  insertKey(7,7, tree1);
  insertKey(3,3, tree1);
  insertKey(1,1, tree1);
     
  printBinTree(tree1);
  printf("-------------------------------------------\n");
  printf("Removing key 3\n");
  printf("-------------------------------------------\n");
  //deleteKey(5, tree1);
  printBinTree(deleteKey(4,tree1));
    
  printf("-------------------------------------------\n");
  printf("Free node \n");
  printf("-------------------------------------------\n");

  tree = freeNode(tree1);
  printBinTree(tree);

  printf("-------------------------------------------\n");
  printf("Free node \n");
  printf("-------------------------------------------\n");
  tree1 = mkNode(5,5,NULL,NULL);

  tree = freeNode(tree1);
  printBinTree(tree);

  printf("-------------------------------------------\n");
  printf("Free tree \n");
  printf("-------------------------------------------\n");
  tree2 = mkNode(5,5,NULL,NULL);
  insertKey(6,6, tree2);
  insertKey(4,4, tree2);
  insertKey(7,7, tree2);
  insertKey(3,3, tree2);
  insertKey(1,1, tree2);
  tree = freeBinTree(tree2);
  printBinTree(tree);

}