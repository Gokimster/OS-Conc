typedef struct BINTREE bintree;

extern bintree *mkNode( int key, int value, bintree *left, bintree *right);

extern bintree *freeNode( bintree *tree);

extern bintree *freeBinTree( bintree *tree);

extern void printBinTree( bintree *tree);

extern bintree *mergeBinTrees( bintree *tree1, bintree *tree2);

extern bintree *insertKey( int key, int value, bintree *tree);

extern bintree *deleteKey( int key, bintree *tree);

extern int findKey( int key, bintree *tree);
