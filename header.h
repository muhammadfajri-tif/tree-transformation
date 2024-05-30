#ifndef header_H
#define header_H
// #include "includes/bool.h"
#include <stdbool.h>
#include <windows.h>

#define Root(P) (P).root
#define IsBinary(P) (P).isBinary
#define IsThreaded(P) (P).isThreaded
#define IsAVL(P) (P).isAVL
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
    bool leftThread;
    bool rightThread;
} Node;

//typedef untuk tree
typedef struct {
    address root;      /**< Pointer to the root node of the tree. */
    bool isBinary;
    bool isThreaded;
    bool isAVL;
} Tree;

// Variabel global untuk keperluan UI
HANDLE hConsole;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
WORD saved_attributes;
CONSOLE_SCREEN_BUFFER_INFO csbi;
COORD WindowsSize;

#include "stack/stack.c"

/******* operasi pada tree *******/
address allocate(infotype info);
void createTree(Tree *t);
void defaultTree(Tree *t);
void insert(Tree *t);
void insertNBTNode(Tree *t, infotype info, infotype parent);
void insertBTNode(Tree *t, infotype info, infotype parent);
address insertAVLNode (address root, infotype info);
void delete(Tree *t);
address deleteNBNode(Tree *t, infotype info);
address deleteBTNode(Tree *t, infotype info);
address deleteAVLNode(address root, infotype info);
address minValueNode(address node);
void update(Tree *t);
void updateNode(Tree *t, infotype info, infotype newInfo);
address search(Tree t, infotype check);
address searchParent(Tree t, infotype check);
bool IsEmpty(Tree t);
address leftRotate(address pivot);
address rightRotate(address pivot);
address copyNode(address Root);
void transform(Tree nbtree, Tree *btree);   //transform NB to B
void balanceToAVL(Tree Btree, address BT, Tree *AVLTree);   //balancing Btree to AVL Tree
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
int level(Tree t, infotype info);
int Max(int a, int b);
int height(address n);
bool isLeaf(Tree t, address n);
int leafAmount(Tree t);
int nodeAmount(Tree t);
int depth(Tree t);
int balanceFactor(address n);
void listNodes(Tree t);
/******************************/

/******* display *******/
void welcome(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void createTreeMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void showTreeTypes(int treeType);
void mainMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void manipulationMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void informationMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void switchTreeMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void transformMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void traverseMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType);
void showTreeDetails(Tree *t, int *treeType);
void PrintTree(Tree t, address P, int Level, bool isBinary);
void PrintTreeVisualization(Tree t, Tree btree, Tree tAVL, int treeType);
void PrintDefaultTreePreview();
void exitProgram();

void gotoxy(int x, int y);
void initSystem();
void printGridUI(char Pesan[], int treeType);
void printc(char JudulMenu[], char JudulTree[]);
void printLine(char line);
void printCenterLine(char line, int StartPos);
void printHalfScreen(char Pesan[], bool isNewLine, bool cancelEnter);
/*********************/

#endif