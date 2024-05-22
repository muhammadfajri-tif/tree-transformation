#ifndef dnbtree_H
#define dnbtree_H
#include "includes/boolean.h"

#define Root(P) (P).root
#define IsBinary(P) (P).isBinary
#define Info(P) (P)->info
#define LeftThread(P) (P)->leftThread
#define RightThread(P) (P)->rightThread
#define FirstSon(P) (P)->leftNode
#define NextBrother(P) (P)->rightNode
#define LeftSon(P) (P)->leftNode
#define RightSon(P) (P)->rightNode
#define NONBINARYTREE 0
#define BINARYTREE 1
#define AVLTREE 2

//typedef untuk variables yang digunakan dalam struktur data
typedef char infotype;
typedef struct eNode *address;

//typedef record untuk setiap node
typedef struct eNode {
    infotype info;          
    address leftNode;       
    address rightNode;       
    boolean leftThread;
    boolean rightThread;
} Node;

//typedef untuk tree
typedef struct {
    address root;      /**< Pointer to the root node of the tree. */
    boolean isBinary;
    boolean isAVL;
} Tree;

#include "stack/stack.c"

/******* operasi pada tree *******/
address allocate(infotype info);
void createTree(Tree *t);
void insert(Tree *t);
void defaultTree(Tree *t);
void insertNBTNode(Tree *t, infotype info, infotype parent);
void insertBTNode(Tree *t, infotype info, infotype parent);
address search(Tree t, infotype check);
address searchParent(Tree t, infotype check);
boolean IsEmpty(Tree t);
void transform(Tree nbtree, Tree *btree);   //transform NB to B
address leftRotate(address pivot);
address rightRotate(address pivot);
address insertAVLNode (address root, infotype info);
void balanceToAVL(address BT, Tree *AVLTree);   //balancing Btree to AVL Tree
void updateTree(Tree *t, Tree *btree, Tree *tAVL);
/********************************/

/******* traversal tree *******/
void preOrder(Tree t, address curr);
void postOrder(Tree t, address curr);
void inOrder(Tree t, address curr);
void levelOrder(Tree t);
void traverse(Tree t);
/******************************/

/******* Threaded *******/
void createThread(Tree *T);
void linkThread(address P, List *Queue, address *prev);
void enqueueInOrder(address P, List *Queue);
/******************************/

/******* operasi lainnya *******/
int max(int a, int b);
int height(address n);
boolean isLeaf(Tree t, address n);
int leafAmount(Tree t);
int nodeAmount(Tree t);
int depth(Tree t);
int level(Tree t, infotype info);
int balanceFactor(address n);
void listNodes(Tree t);
void update(Tree *t);
void updateNode(Tree *t, infotype info, infotype newInfo);
address deleteNBNode(Tree *t, infotype info);
/******************************/

/******* display *******/
void createTreeMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void mainMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void manipulationMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void informationMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void switchTreeMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void transformMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void traverseMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void showTreeDetails(Tree *t, int *treeType);
void PrintTree(address P, int Level, boolean isBinary);
/*********************/

#endif