#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN64) || defined(_WIN32)
#include <conio.h>
#endif
#include "header.h"
#include "includes/config.h"

address allocate(infotype info)
{
    address node;
    node = (address)malloc(sizeof(Node));
    if (node != NULL)
    {
        node->info = info;
        node->leftNode = NULL;
        node->rightNode = NULL;
        node->leftThread = false;
        node->rightThread = false;
    }
    return node;
}

void createTree(Tree *t)
{
    address newNode;
    infotype info;

    printf("\nMasukkan info untuk root = ");
    scanf(" %c", &info);
    newNode = allocate(info);
    if (newNode != NULL)
    {
        t->root = newNode;
    }
    t->isBinary = false;
    t->isAVL = false;
    insert(t);
}

void insertNBTNode(Tree *t, infotype info, infotype parent)
{
    address curr, brother;
    curr = search(*t, parent);
    if (FirstSon(curr) == NULL)
    {
        FirstSon(curr) = allocate(info);
    }
    else
    {
        brother = FirstSon(curr);
        while (NextBrother(brother) != NULL)
        {
            brother = NextBrother(brother);
        }
        NextBrother(brother) = allocate(info);
    }
}

void insertBTNode(Tree *t, infotype info, infotype parent)
{
    address parentNode = search(*t, parent);
    if (parentNode != NULL)
    {
        if (LeftThread(parentNode) || LeftSon(parentNode) == NULL)
        {
            LeftSon(parentNode) = allocate(info);
        }
        else if (RightThread(parentNode) || RightSon(parentNode) == NULL)
        {
            RightSon(parentNode) = allocate(info);
        }

        if (IsThreaded(*t))
        {
            createThread(t); // Update Thread
        }
        
    }
    else
    {
        printf("Parent tidak ditemukan\n");
    }
}

void insert(Tree *t)
{
    infotype info, parent;
    int i, j;

    if (t->isBinary != true || t->isBinary == true && t->isAVL == false)
    {
        printf("insert Tree");
        if (t->root == NULL)
        {
            printf("\nMasukkan info untuk root = ");
            scanf(" %c", &info);
            t->root = allocate(info);
        }
        printf("\nMasukkan jumlah node yang ingin dimasukkan = ");
        scanf("%d", &i);
        for (j = 0; j < i; j++)
        {
            PLATFORM_NAME == "windows" ? system("cls") : system("clear");
            printf("===== Input Tree =====\n");
            PrintTree(t->root, 0, t->isBinary);
            printf("\nList node dalam tree: ");
            listNodes(*t);
        inputNODE:
            printf("\nMasukkan info node baru ke-%d = ", j + 1);
            scanf(" %c", &info);
            if (search(*t, info) == NULL)
            {
            inputParent:
                printf("Masukkan info parent node baru ke-%d = ", j + 1);
                scanf(" %c", &parent);
                if (search(*t, parent) != NULL)
                {
                    if (t->isBinary == true)
                    {
                        if (LeftSon(search(*t, parent)) != NULL && RightSon(search(*t, parent)) != NULL)
                        {
                            printf("\nParent dengan info %c sudah memiliki 2 anak!\n", parent);
                            goto inputParent;
                        }
                        insertBTNode(t, info, parent);
                    }
                    else
                    {
                        insertNBTNode(t, info, parent);
                    }
                    PrintTree(t->root, 0, t->isBinary);
                    printf("Node dengan info %c berhasil dimasukkan\n", info);
                    printf("ketik untuk melanjutkan...");
                    PLATFORM_NAME == "windows" ? getch() : getchar();
                }
                else
                {
                    printf("Parent dengan info %c tidak ditemukan, silahkan masukkan kembali\n", parent);
                    goto inputParent;
                }
            }
            else
            {
                printf("\nInfo Node Yang Anda Input Sudah Ada! Mohon Input Info Node Yang Unik!");
                goto inputNODE;
            }
        }
    }
    else
    {
        if (t->root == NULL)
        {
            printf("\nMasukkan info untuk root = ");
            scanf(" %c", &info);
            t->root = allocate(info);
        }
        printf("\nMasukkan jumlah node yang ingin dimasukkan = ");
        scanf("%d", &i);
        for (j = 0; j < i; j++)
        {
            PLATFORM_NAME == "windows" ? system("cls") : system("clear");
            printf("===== Input Tree =====\n");
            PrintTree(t->root, 0, t->isBinary);
            printf("\nList node dalam tree : ");
            listNodes(*t);
        inputNode:
            printf("\nMasukkan info node baru ke-%d = ", j + 1);
            scanf(" %c", &info);
            if (search(*t, info) == NULL)
            {
                (*t).root = insertAVLNode(t->root, info);
                PrintTree(t->root, 0, t->isBinary);
                printf("Node dengan info %c berhasil dimasukkan\n", info);
                printf("ketik untuk melanjutkan...");
                PLATFORM_NAME == "windows" ? getch() : getchar();
            }
            else
            {
                printf("\nInfo Node Yang Anda Input Sudah Ada! Mohon Input Info Node Yang Unik!");
                goto inputNode;
            }
        }
    }
}

void delete(Tree *t)
{
    infotype info;
deleteNode:
    PLATFORM_NAME == "windows" ? system("cls") : system("clear");
    PrintTree(t->root, 0, t->isBinary);
    printf("\nList node :");
    listNodes(*t);
    printf("\nMasukkan Info Node Yang Ingin Dihapus = ");
    scanf(" %c", &info);
    if (search(*t, info) != NULL)
    {
        if (!t->isBinary)
        {
            deleteNBNode(t, info);
        }
        else if (t->isBinary == true && t->isAVL == false)
        {
            deleteBTNode(t, info);
        }
        else if (t->isBinary == true && t->isAVL == true)
        {
            // delete AVL tree
        }
        if (t->root != NULL)
        {
            PrintTree(t->root, 0, t->isBinary);
        }
        printf("Node dengan info %c berhasil dihapus\n", info);
    }
    else
    {
        printf("\nNode Tidak Ditemukan! Masukkan Info Node Yang Benar!\n");
        goto deleteNode;
    }
}

address deleteNBNode(Tree *t, infotype info)
{
    address curr, linkedNodes;
    curr = search(*t, info);
    if (curr != NULL)
    {
        linkedNodes = searchParent(*t, info);
        if (linkedNodes->leftNode->info == info)
        {
            linkedNodes->leftNode = NULL;
            free(curr);
            return curr;
        }
        else
        {
            linkedNodes = searchParent(*t, info)->leftNode;
            while (linkedNodes->rightNode->info != info)
            {
                linkedNodes = linkedNodes->rightNode;
            }
            linkedNodes->rightNode = NULL;
            free(curr);
            return curr;
        }
    }
}

address deleteBTNode(Tree *t, infotype info)
{
    address curr, parent;
    curr = search(*t, info);
    if (curr != NULL)
    {
        parent = searchParent(*t, info);
        if (LeftSon(parent) != NULL && Info(LeftSon(parent)) == info)
        {
            LeftSon(parent) = NULL;
            free(curr);
            return curr;
        }
        else
        {
            RightSon(parent) = NULL;
            free(curr);
            return curr;
        }
    }
}

void defaultTree(Tree *t)
{
    t->root = allocate('S');
    t->isBinary = false;
    t->isThreaded = false;
    t->isAVL = false;

    insertNBTNode(t, 'I', 'S');
    insertNBTNode(t, 'A', 'S');
    insertNBTNode(t, 'G', 'I');
    insertNBTNode(t, 'M', 'I');
    insertNBTNode(t, 'O', 'A');
    insertNBTNode(t, 'H', 'A');
    insertNBTNode(t, '1', 'H');
    insertNBTNode(t, '0', 'H');
}

// Function Search Tree
address search(Tree t, infotype check)
{
    if (t.isBinary != true)
    {
        List stack;
        CreateList(&stack);
        push(&stack, NULL);
        address curr;
        boolean resmi;

        curr = t.root;
        resmi = true;
        while (curr != NULL)
        {
            if (resmi)
            {
                if (Info(curr) == check)
                {
                    return curr;
                }
            }
            if (FirstSon(curr) != NULL && resmi)
            {
                push(&stack, curr);
                curr = FirstSon(curr);
            }
            else
            {
                if (NextBrother(curr) != NULL)
                {
                    curr = NextBrother(curr);
                    resmi = true;
                }
                else
                {
                    curr = pull(&stack);
                    resmi = false;
                }
            }
        }
    }
    else
    {
        List Queue;
        CreateList(&Queue);
        address current = t.root;
        address currentChild = NULL;

        if (current != NULL)
        {
            if (Info(current) == check)
            {
                return current;
            }
            while (current != NULL || Queue.First != NULL)
            {
                if (LeftSon(current) != NULL)
                {
                    if (Info(LeftSon(current)) == check)
                    {
                        return LeftSon(current);
                    }
                    if (LeftSon(LeftSon(current)) != NULL || RightSon(LeftSon(current)) != NULL)
                    {
                        enqueue(&Queue, LeftSon(current));
                    }
                }

                if (RightSon(current) != NULL)
                {
                    if (Info(RightSon(current)) == check)
                    {
                        return RightSon(current);
                    }
                    if (LeftSon(RightSon(current)) != NULL || RightSon(RightSon(current)) != NULL)
                    {
                        enqueue(&Queue, RightSon(current));
                    }
                }

                if (Queue.First != NULL)
                {
                    current = dequeue(&Queue);
                }
                else
                {
                    current = NULL;
                }
            }
        }
        return NULL;
    }
}

// Function Search Parent Tree
address searchParent(Tree t, infotype check)
{
    if (!t.isBinary)
    {
        List stack;
        CreateList(&stack);
        push(&stack, NULL);
        address curr;
        boolean resmi;

        curr = t.root;
        resmi = true;
        while (curr != NULL)
        {
            if (resmi)
            {
                if (Info(curr) == check)
                {
                    return pull(&stack); // return parent
                }
            }
            if (!LeftThread(curr) && FirstSon(curr) != NULL && resmi)
            {
                push(&stack, curr);
                curr = FirstSon(curr);
            }
            else
            {
                if (!LeftThread(curr) && FirstSon(curr) != NULL)
                {
                    curr = NextBrother(curr);
                    resmi = true;
                }
                else
                {
                    curr = pull(&stack);
                    resmi = false;
                }
            }
        }
    }
    else
    {
        List Queue;
        CreateList(&Queue);
        address current = t.root;
        address currentChild = NULL;

        if (current != NULL)
        {
            if (Info(current) == check)
            {
                return NULL;
            }
            while (current != NULL || Queue.First != NULL)
            {
                if (LeftSon(current) != NULL && LeftThread(current) == false)
                {
                    if (Info(LeftSon(current)) == check)
                    {
                        return current;
                    }
                    if (LeftSon(LeftSon(current)) != NULL || RightSon(LeftSon(current)) != NULL)
                    {
                        enqueue(&Queue, LeftSon(current));
                    }
                }

                if (RightSon(current) != NULL && RightThread(current) == false)
                {
                    if (Info(RightSon(current)) == check)
                    {
                        return current;
                    }
                    if (LeftSon(RightSon(current)) != NULL || RightSon(RightSon(current)) != NULL)
                    {
                        enqueue(&Queue, RightSon(current));
                    }
                }

                if (Queue.First != NULL)
                {
                    current = dequeue(&Queue);
                }
                else
                {
                    current = NULL;
                }
            }
        }
    }
}

boolean IsEmpty(Tree t)
{
    if (t.root == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void transform(Tree nbtree, Tree *btree)
{
    address curr = nbtree.root;
    *btree = nbtree;
    (*btree).isBinary = true;
    (*btree).isThreaded = false;
}

address leftRotate(address pivot)
{
    address y = RightSon(pivot);
    address z = LeftSon(y);
    RightSon(pivot) = z;
    LeftSon(y) = pivot;
    return y;
}

address rightRotate(address pivot)
{
    address y = LeftSon(pivot);
    address z = RightSon(y);
    LeftSon(pivot) = z;
    RightSon(y) = pivot;
    return y;
}

address insertAVLNode(address root, infotype info)
{
    if (root == NULL)
    {
        return allocate(info);
    }
    else
    {
        if (info < root->info)
        {
            LeftSon(root) = insertAVLNode(LeftSon(root), info);
        }
        else
        {
            RightSon(root) = insertAVLNode(RightSon(root), info);
        }
    }

    int balance = balanceFactor(root);
    // Right Right Case
    if (balance > 1 && info > Info(RightSon(root)))
    {
        return leftRotate(root);
    }
    // Left Left Case
    if (balance < -1 && info < Info(LeftSon(root)))
    {
        return rightRotate(root);
    }
    // Right Left Case
    if (balance > 1 && info < Info(RightSon(root)))
    {
        RightSon(root) = rightRotate(RightSon(root));
        return leftRotate(root);
    }
    // Left Right Case
    if (balance < -1 && info > Info(LeftSon(root)))
    {
        LeftSon(root) = leftRotate(LeftSon(root));
        return rightRotate(root);
    }

    return root;
}

void balanceToAVL(address BT, Tree *AVLTree)
{
    if (BT != NULL && (*AVLTree).isBinary == true)
    {
        (*AVLTree).root = insertAVLNode(Root(*AVLTree), Info(BT));
        balanceToAVL(LeftSon(BT), AVLTree);
        balanceToAVL(RightSon(BT), AVLTree);
    }
    else
    {
    }
}

void updateTree(Tree *t, Tree *btree, Tree *tAVL)
{
    transform(*t, btree);
    tAVL->isBinary = true;
    balanceToAVL(btree->root, tAVL);
}

void preOrder(Tree t, address node)
{
    if (!IsEmpty(t))
    {
        // preOrder versi non-binary tree
        if (t.isBinary != true)
        {
            List stack;
            CreateList(&stack);
            push(&stack, NULL);
            address curr;
            boolean resmi;

            curr = t.root;
            resmi = true;
            while (curr != NULL)
            {
                if (resmi)
                {
                    printf("%c ", Info(curr));
                }
                if (!LeftThread(curr) && FirstSon(curr) != NULL && resmi)
                {
                    push(&stack, curr);
                    curr = FirstSon(curr);
                }
                else
                {
                    if (!RightThread(curr) &&NextBrother(curr) != NULL)
                    {
                        curr = NextBrother(curr);
                        resmi = true;
                    }
                    else
                    {
                        curr = pull(&stack);
                        resmi = false;
                    }
                }
            }
        }
        else
        {
            // preOrder versi binary tree
            if (node != NULL)
            {
                printf("%c ", node->info);
                if (!LeftThread(node))
                {
                    preOrder(t, LeftSon(node));
                }
                if (!RightThread(node))
                {
                    preOrder(t, RightSon(node));
                }
            }
        }
    }
    else
    {
        printf("Tree Kosong!");
    }
}

void postOrder(Tree t, address node)
{
    if (!IsEmpty(t))
    {
        // postOrder versi non-binary tree
        if (t.isBinary != true)
        {
            List stack;
            CreateList(&stack);
            push(&stack, NULL);
            address curr;
            boolean resmi;

            curr = t.root;
            resmi = true;
            while (curr != NULL)
            {
                if (!LeftThread(curr) && FirstSon(curr) != NULL && resmi)
                {
                    push(&stack, curr);
                    curr = FirstSon(curr);
                }
                else
                {
                    printf("%c ", Info(curr));
                    if (!RightThread(curr) && NextBrother(curr) != NULL)
                    {
                        curr = NextBrother(curr);
                        resmi = true;
                    }
                    else
                    {
                        curr = pull(&stack);
                        resmi = false;
                    }
                }
            }
        }
        else
        {
            // masukin postOrder versi binary tree
            if (node != NULL)
            {
                if (!LeftThread(node))
                {
                    postOrder(t, LeftSon(node));
                }
                if (!RightThread(node))
                {
                    postOrder(t, RightSon(node));
                }
                printf("%c ", node->info);
            }
        }
    }
    else
    {
        printf("Tree Kosong!");
    }
}

void inOrder(Tree t, address node)
{
    if (!IsEmpty(t))
    {
        // inOrder versi non-binary tree
        if (t.isBinary != true)
        {
            List stack;
            CreateList(&stack);
            push(&stack, NULL);
            address curr, parent;
            boolean resmi;

            curr = t.root;
            resmi = true;
            while (curr != NULL)
            {
                if (!LeftThread(curr) && FirstSon(curr) != NULL && resmi)
                {
                    push(&stack, curr);
                    curr = FirstSon(curr);
                }
                else
                {
                    if (resmi)
                    {
                        printf("%c ", Info(curr));
                    }
                    parent = pull(&stack);
                    if (parent == NULL)
                    {
                        break;
                    }
                    if (curr == FirstSon(parent))
                    {
                        printf("%c ", Info(parent));
                    }
                    push(&stack, parent);

                    if (!RightThread(curr) && NextBrother(curr) != NULL)
                    {
                        curr = NextBrother(curr);
                        resmi = true;
                    }
                    else
                    {
                        curr = pull(&stack);
                        resmi = false;
                    }
                }
            }
        }
        else
        {
            // inOrder versi binary tree
            if (node != NULL)
            {
                if (!LeftThread(node))
                {
                    inOrder(t, LeftSon(node));
                }
                printf("%c ", Info(node));
                if (!RightThread(node))
                {
                    inOrder(t, RightSon(node));
                }
            }
        }
    }
    else
    {
        printf("Tree Kosong!");
    }
}

void levelOrder(Tree t)
{
    if (!IsEmpty(t))
    {
        // levelOrder versi non-binary tree
        if (t.isBinary != true)
        {
            List Queue;
            CreateList(&Queue);
            address current;
            current = t.root;
            printf("%c ", Info(current));

            current = FirstSon(current);
            while (current != NULL)
            {
                printf("%c ", Info(current));
                if (FirstSon(current) != NULL)
                {
                    enqueue(&Queue, FirstSon(current));
                }
                if (NextBrother(current) != NULL)
                {
                    current = NextBrother(current);
                }
                else
                {
                    if (!ListEmpty(Queue))
                    {
                        current = dequeue(&Queue);
                    }
                    else
                    {
                        current = NULL;
                    }
                }
            }
        }
        else
        { // levelOrder versi binary tree
            List Queue;
            CreateList(&Queue);
            address current = t.root;
            address currentChild = NULL;

            if (current != NULL)
            {
                printf("%c ", Info(current));
                while (current != NULL || Queue.First != NULL)
                {
                    if (LeftSon(current) != NULL && LeftThread(current) == false)
                    {
                        printf("%c ", Info(LeftSon(current)));
                        if (LeftSon(LeftSon(current)) != NULL || RightSon(LeftSon(current)) != NULL)
                        {
                            enqueue(&Queue, LeftSon(current));
                        }
                    }

                    if (RightSon(current) != NULL && RightThread(current) == false)
                    {
                        printf("%c ", Info(RightSon(current)));
                        if (LeftSon(RightSon(current)) != NULL || RightSon(RightSon(current)) != NULL)
                        {
                            enqueue(&Queue, RightSon(current));
                        }
                    }

                    if (Queue.First != NULL)
                    {
                        current = dequeue(&Queue);
                    }
                    else
                    {
                        current = NULL;
                    }
                }
            }
        }
    }
    else
    {
        printf("Tree Kosong!");
    }
}

void traverse(Tree t)
{
    printf("Pre order: ");
    preOrder(t, t.root);
    printf("\nPost order: ");
    postOrder(t, t.root);
    printf("\nIn order: ");
    inOrder(t, t.root);
    printf("\nLevel order: ");
    levelOrder(t);
}

void createThread(Tree *T)
{
    List Queue;
    address prev = NULL;
    CreateList(&Queue);

    enqueueInOrder(Root(*T), &Queue);

    linkThread(Root(*T), &Queue, &prev);

    IsThreaded(*T) = true;
}

void linkThread(address P, List *Queue, address *prev)
{
    if (P == NULL)
    {
        return;
    }

    if (!LeftThread(P) && LeftSon(P) != NULL)
    {
        linkThread(LeftSon(P), Queue, prev);
    }
    else
    {
        if (First(*Queue) != Nil)
        {
            LeftSon(P) = *prev;
            LeftThread(P) = true;
        }
        else
        {
            LeftSon(P) = NULL;
        }
    }

    *prev = dequeue(Queue);

    if (!RightThread(P) && RightSon(P) != NULL)
    {
        linkThread(RightSon(P), Queue, prev);
    }
    else
    {
        if (First(*Queue) != Nil)
        {
            RightSon(P) = getFront(*Queue);
            RightThread(P) = true;
        }
        else
        {
            RightSon(P) = NULL;
        }
    }
}

void enqueueInOrder(address P, List *Queue)
{
    if (P == NULL)
    {
        return;
    }

    if (!LeftThread(P) && LeftSon(P) != NULL)
    {
        enqueueInOrder(LeftSon(P), Queue);
    }

    enqueue(Queue, P);

    if (!RightThread(P) && RightSon(P) != NULL)
    {
        enqueueInOrder(RightSon(P), Queue);
    }
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int height(address n)
{
    if (n == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + max(height(LeftThread(n) ? NULL : n->leftNode), height(RightThread(n) ? NULL : n->rightNode));
    }
}

boolean isLeaf(Tree t, address n)
{
    if (t.isBinary == true)
    {
        if ((LeftThread(n) && RightThread(n)) || (LeftSon(n) == NULL && RightSon(n) == NULL))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (n->leftNode == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

int leafAmount(Tree t)
{
    // menghitung jumlah leaf pada tree dengan pre order non binary traversal
    List stack;
    CreateList(&stack);
    push(&stack, NULL);
    address curr;
    boolean resmi;
    int count = 0;

    curr = t.root;
    resmi = true;
    while (curr != NULL)
    {
        if (resmi)
        {
            if (isLeaf(t, curr))
            {
                count++;
            }
        }
        if (!LeftThread(curr) && FirstSon(curr) != NULL && resmi)
        {
            push(&stack, curr);
            curr = FirstSon(curr);
        }
        else
        {
            if (!RightThread(curr) && NextBrother(curr) != NULL)
            {
                curr = NextBrother(curr);
                resmi = true;
            }
            else
            {
                curr = pull(&stack);
                resmi = false;
            }
        }
    }
    return count;
}

int nodeAmount(Tree t)
{

    List stack;
    CreateList(&stack);
    push(&stack, NULL);
    address curr;
    int count = 0;
    boolean resmi;

    curr = t.root;
    resmi = true;
    while (curr != NULL)
    {
        if (resmi)
        {
            count++;
        }
        if (!LeftThread(curr) && FirstSon(curr) != NULL && resmi)
        {
            push(&stack, curr);
            curr = FirstSon(curr);
        }
        else
        {
            if (!RightThread(curr) && NextBrother(curr) != NULL)
            {
                curr = NextBrother(curr);
                resmi = true;
            }
            else
            {
                curr = pull(&stack);
                resmi = false;
            }
        }
    }

    return count;
}

int depth(Tree t)
{
    int count = 0;
    if (!IsEmpty(t))
    {
        if (!t.isBinary)
        {
            List Queue;
            CreateList(&Queue);
            address current;
            current = t.root;

            current = FirstSon(current);
            while (current != NULL)
            {
                if (FirstSon(current) != NULL)
                {
                    enqueue(&Queue, FirstSon(current));
                }
                if (NextBrother(current) != NULL)
                {
                    current = NextBrother(current);
                }
                else
                {
                    if (!ListEmpty(Queue))
                    {
                        current = dequeue(&Queue);
                        count++;
                    }
                    else
                    {
                        current = NULL;
                    }
                }
            }
        }
        else
        {
            List Queue;
            CreateList(&Queue);
            address current = t.root;
            address currentChild = NULL;

            if (current != NULL)
            {
                while (current != NULL || Queue.First != NULL)
                {
                    if (LeftSon(current) != NULL && LeftThread(current) == false)
                    {
                        if ((!LeftThread(LeftSon(current)) && LeftSon(LeftSon(current)) != NULL) || (!RightThread(LeftSon(current)) && RightSon(LeftSon(current)) != NULL))
                        {
                            enqueue(&Queue, LeftSon(current));
                            count++;
                        }
                    }

                    if (RightSon(current) != NULL && RightThread(current) == false)
                    {
                        if ((!LeftThread(RightSon(current)) && LeftSon(RightSon(current)) != NULL) || (!RightThread(RightSon(current)) && RightSon(RightSon(current)) != NULL))
                        {
                            enqueue(&Queue, RightSon(current));
                            count++;
                        }
                    }

                    if (Queue.First != NULL)
                    {
                        current = dequeue(&Queue);
                    }
                    else
                    {
                        current = NULL;
                    }
                }
            }
        }
        return count;
    }
    else
    {
        printf("Tree Kosong!");
    }
}

int level(Tree t, infotype info)
{
    address cur = search(t, info);
    int level = 0;
    while (searchParent(t, cur->info) != NULL)
    {
        level++;
        cur = searchParent(t, cur->info);
    }
    return level;
}

int balanceFactor(address n)
{
    return height(RightSon(n)) - height(LeftSon(n));
}

void listNodes(Tree t)
{
    levelOrder(t);
}

void update(Tree *t)
{
    infotype info, newInfo;
    address curr;
inputUpdatedNode:
    printf("\nList node :");
    listNodes(*t);
    printf("\nMasukkan Info Node Yang Ingin Diupdate = ");
    scanf(" %c", &info);
    curr = search(*t, info);
    if (curr != NULL)
    {
    inputNewInfo:
        printf("\nMasukkan Info Baru = ");
        scanf(" %c", &newInfo);
        if (search(*t, newInfo) == NULL)
        {
            updateNode(t, info, newInfo);
        }
        else
        {
            printf("\nInfo Node Yang Anda Input Sudah Ada! Mohon Input Info Node Yang Unik!");
            goto inputNewInfo;
        }
    }
    else
    {
        printf("\nNode Tidak Ditemukan!");
        goto inputUpdatedNode;
    }
}

void updateNode(Tree *t, infotype info, infotype newInfo)
{
    Info(search(*t, info)) = newInfo;
}

void PrintTree(address P, int Level, boolean isBinary)
{
    if (P != NULL)
    {
        int i = 1;
        for (i = 1; i <= Level; i++)
        {
            if (i < Level)
            {
                printf("|  ");
            }
            else
            {
                printf("|--");
            }
        }
        printf("%c\n", Info(P));
        if (!LeftThread(P))
        {
            PrintTree(LeftSon(P), Level + 1, isBinary);
        }
        if (isBinary)
        {
            Level++;
        }
        if (!RightThread(P))
        {
            PrintTree(NextBrother(P), Level, isBinary);
        }
    }
}