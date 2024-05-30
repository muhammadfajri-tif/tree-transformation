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

    printHalfScreen("Masukkan info untuk root = ", true, false);
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
            if (LeftThread(parentNode))
            {
                LeftThread(parentNode) = false;
            }
        }
        else if (RightThread(parentNode) || RightSon(parentNode) == NULL)
        {
            RightSon(parentNode) = allocate(info);
            if (RightThread(parentNode))
            {
                RightThread(parentNode) = false;
            }
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
    address parentNode;
    int i, j, treeType;
    char pesan[100];

    if (!IsBinary(*t))
    {
        treeType = NONBINARYTREE;
    }
    else if (!IsAVL(*t))
    {
        treeType = BINARYTREE;
    }
    else
    {
        treeType = AVLTREE;
    }

    if (t->isBinary != true || (t->isBinary == true && t->isAVL == false))
    {
        PLATFORM_NAME == "windows" ? system("cls") : system("clear");
        printGridUI("Insert Tree", treeType);
        PrintTree(t->root, 0, t->isBinary);
        gotoxy(0, 4);
        if (t->root == NULL)
        {
            printHalfScreen("Masukkan info untuk root = ", false, false);
            scanf(" %c", &info);
            t->root = allocate(info);
        }
        printHalfScreen("Masukkan jumlah node yang ingin dimasukkan = ", t->root == NULL ? true : false, false);
        scanf("%d", &i);
        for (j = 0; j < i; j++)
        {
            PLATFORM_NAME == "windows" ? system("cls") : system("clear");
            printGridUI("Insert Tree", treeType);
            PrintTree(t->root, 0, t->isBinary);
            gotoxy(0, 4);
            printHalfScreen("List node dalam tree: ", false, false);
            listNodes(*t);
        inputNODE:
            sprintf(pesan, "Masukkan info node baru ke-%d = ", j + 1);
            printHalfScreen(pesan, true, false);
            scanf(" %c", &info);
            if (search(*t, info) == NULL)
            {
            inputParent:
                sprintf(pesan, "Masukkan info parent node baru ke-%d = ", j + 1);
                printHalfScreen(pesan, false, false);
                scanf(" %c", &parent);
                parentNode = search(*t, parent);
                if (parentNode != NULL)
                {
                    if (t->isBinary == true)
                    {
                        if (!LeftThread(parentNode) && LeftSon(parentNode) != NULL && !RightThread(parentNode) && RightSon(parentNode) != NULL)
                        {
                            sprintf(pesan, "Parent dengan info %c sudah memiliki 2 anak!\n", parent);
                            printHalfScreen(pesan, true, false);
                            goto inputParent;
                        }
                        insertBTNode(t, info, parent);
                    }
                    else
                    {
                        insertNBTNode(t, info, parent);
                    }
                    PLATFORM_NAME == "windows" ? system("cls") : system("clear");
                    printGridUI("Insert Tree", treeType);
                    PrintTree(t->root, 0, t->isBinary);
                    gotoxy(0, 4);
                    sprintf(pesan, "Node dengan info %c berhasil dimasukkan\n", info);
                    printHalfScreen(pesan, false, false);
                    printHalfScreen("ketik untuk melanjutkan...", true, false);
                    PLATFORM_NAME == "windows" ? getch() : getchar();
                }
                else
                {
                    sprintf(pesan, "Parent dengan info %c tidak ditemukan, silahkan masukkan kembali\n", parent);
                    printHalfScreen(pesan, true, false);
                    goto inputParent;
                }
            }
            else
            {
                printHalfScreen("Info Node Yang Anda Input Sudah Ada! Mohon Input Info Node Yang Unik!", true, false);
                goto inputNODE;
            }
        }
    }
    else
    {
        PLATFORM_NAME == "windows" ? system("cls") : system("clear");
        printGridUI("Insert Tree", treeType);
        PrintTree(t->root, 0, t->isBinary);
        gotoxy(0, 4);
        if (t->root == NULL)
        {
            printHalfScreen("Masukkan info untuk root = ", false, false);
            scanf(" %c", &info);
            t->root = allocate(info);
        }
        printHalfScreen("Masukkan jumlah node yang ingin dimasukkan = ", t->root == NULL ? true : false, false);
        scanf("%d", &i);
        for (j = 0; j < i; j++)
        {
            PLATFORM_NAME == "windows" ? system("cls") : system("clear");
            printGridUI("Insert Tree", treeType);
            PrintTree(t->root, 0, t->isBinary);
            gotoxy(0, 4);
            printHalfScreen("List node dalam tree: ", false, false);
            listNodes(*t);
        inputNode:
            sprintf(pesan, "Masukkan info node baru ke-%d = ", j + 1);
            printHalfScreen(pesan, false, false);
            scanf(" %c", &info);
            if (search(*t, info) == NULL)
            {
                (*t).root = insertAVLNode(t->root, info);
                PLATFORM_NAME == "windows" ? system("cls") : system("clear");
                printGridUI("Insert Tree", treeType);
                PrintTree(t->root, 0, t->isBinary);
                gotoxy(0, 4);
                sprintf(pesan, "Node dengan info %c berhasil dimasukkan\n", info);
                printHalfScreen(pesan, false, false);
                printHalfScreen("ketik untuk melanjutkan...", true, false);
                PLATFORM_NAME == "windows" ? getch() : getchar();
            }
            else
            {
                printHalfScreen("Info Node Yang Anda Input Sudah Ada! Mohon Input Info Node Yang Unik!", true, false);
                goto inputNode;
            }
        }
    }
}

void delete(Tree *t)
{
    infotype info;
    int treeType;
    char pesan[50];

    if (!IsBinary(*t))
    {
        treeType = NONBINARYTREE;
    }
    else if (!IsAVL(*t))
    {
        treeType = BINARYTREE;
    }
    else
    {
        treeType = AVLTREE;
    }
deleteNode:
    PLATFORM_NAME == "windows" ? system("cls") : system("clear");
    printGridUI("Delete Node", treeType);
    PrintTree(t->root, 0, t->isBinary);
    gotoxy(0, 4);
    printHalfScreen("List node :", false, false);
    listNodes(*t);
    printHalfScreen("Masukkan Info Node Yang Ingin Dihapus = ", true, false);
    scanf(" %c", &info);
    if(info == t->root->info){
        printHalfScreen("Tidak bisa menghapus root!", true, false);
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto deleteNode;
    }
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
            deleteAVLNode(t->root, info);
        }
        PLATFORM_NAME == "windows" ? system("cls") : system("clear");
        printGridUI("Delete Node", treeType);
        PrintTree(t->root, 0, t->isBinary);
        gotoxy(0, 4);
        sprintf(pesan, "Node dengan info %c berhasil dihapus\n", info);
        printHalfScreen(pesan, false, false);
    }
    else
    {
        printHalfScreen("Node Tidak Ditemukan! Masukkan Info Node Yang Benar!\n", true, false);
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
        if (linkedNodes->leftNode->info == info) // Jika merupakan left node/first son
        {
            linkedNodes->leftNode = NextBrother(curr);
            NextBrother(curr) = NULL;
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
            linkedNodes->rightNode = NextBrother(curr);
            NextBrother(curr) = NULL;
            free(curr);
            return curr;
        }
    }
}

address deleteBTNode(Tree *t, infotype info)
{
    if (IsThreaded(*t))
    {
        address current, currentChild, node, successor, nodeParent, successorParent, tempL, tempR, traverseNode;
        List Queue, Queue2;
        CreateList(&Queue);
        enqueueInOrder(Root(*t), &Queue);
        push(&Queue, NULL);
        node = search(*t, info);
        successor = Info(Search(Queue, node)->next);
        if (node != NULL)
        {
            if (node != Root(*t)) // Jika node yang dihapus bukan root
            {
                nodeParent = searchParent(*t, info);
                if (!isLeaf(*t, node))
                {
                    if (Info(LeftSon(nodeParent)) == info) // Jika merupakan left son
                    {
                        if (!RightThread(node) && RightSon(node) != NULL) // Jika memiliki right son
                        {
                            if (!LeftThread(node) && LeftSon(node) != NULL) // Jika memiliki left son
                            {
                                tempL = LeftSon(node);
                                tempR = LeftSon(RightSon(node));
                                CreateList(&Queue2);
                                current = RightSon(node);
                                currentChild = NULL;

                                // traversal right son until found NULL
                                if (current != NULL)
                                {
                                    // attach condition
                                    if (LeftThread(current) || LeftSon(current) == NULL)
                                    {
                                        LeftSon(current) = tempR;
                                        LeftThread(current) = false;
                                        LeftSon(RightSon(node)) = LeftSon(node);
                                        LeftSon(node) = NULL;
                                        goto TraverseLeftEnd;
                                    }
                                    else if (RightThread(current) || RightSon(current) == NULL)
                                    {
                                        RightSon(current) = tempR;
                                        RightThread(current) = false;
                                        LeftSon(RightSon(node)) = LeftSon(node);
                                        LeftSon(node) = NULL;
                                        goto TraverseLeftEnd;
                                    }

                                    // traversal
                                    while (current != NULL || Queue2.First != NULL)
                                    {
                                        if (LeftSon(current) != NULL && LeftThread(current) == false)
                                        {
                                            if (LeftThread(LeftSon(current)) || LeftSon(LeftSon(current)) == NULL)
                                            {
                                                LeftSon(LeftSon(current)) = tempL;
                                                LeftThread(LeftSon(current)) = false;
                                                goto TraverseLeftEnd;
                                            }
                                            else if (RightThread(LeftSon(current)) || RightSon(LeftSon(current)) == NULL)
                                            {
                                                RightSon(LeftSon(current)) = tempL;
                                                RightThread(LeftSon(current)) = false;
                                                goto TraverseLeftEnd;
                                            }

                                            if (LeftSon(LeftSon(current)) != NULL || RightSon(LeftSon(current)) != NULL)
                                            {
                                                enqueue(&Queue2, LeftSon(current));
                                            }
                                        }

                                        if (RightSon(current) != NULL && RightThread(current) == false)
                                        {
                                            if (LeftThread(RightSon(current)) || LeftSon(RightSon(current)) == NULL)
                                            {
                                                LeftSon(RightSon(current)) = tempL;
                                                LeftThread(RightSon(current)) = false;
                                                goto TraverseLeftEnd;
                                            }
                                            else if (RightThread(RightSon(current)) || RightSon(RightSon(current)) == NULL)
                                            {
                                                RightSon(RightSon(current)) = tempL;
                                                RightThread(RightSon(current)) = tempL;
                                                goto TraverseLeftEnd;
                                            }

                                            if (LeftSon(RightSon(current)) != NULL || RightSon(RightSon(current)) != NULL)
                                            {
                                                enqueue(&Queue2, RightSon(current));
                                            }
                                        }

                                        if (Queue2.First != NULL)
                                        {
                                            current = dequeue(&Queue2);
                                        }
                                        else
                                        {
                                            current = NULL;
                                        }
                                    }
                                }
                            }
                        TraverseLeftEnd:
                            LeftSon(nodeParent) = RightSon(node);
                            RightSon(node) = NULL;
                            free(node);
                            return node;
                        }
                        else // Jika tidak memiliki right son (thread)
                        {
                            LeftSon(nodeParent) = LeftSon(node);
                            LeftSon(node) = NULL;
                            RightSon(node) = NULL;
                            free(node);
                            return node;
                        }
                    }
                    else // Jika merupakan right son
                    {
                        if (!RightThread(node) && RightSon(node) != NULL) // Jika memiliki right son
                        {
                            if (!LeftThread(node) && LeftSon(node) != NULL) // Jika memiliki left son
                            {
                                tempL = LeftSon(node);
                                tempR = LeftSon(RightSon(node));
                                current = RightSon(node);

                                // traversal right son until found NULL
                                CreateList(&Queue2);
                                currentChild = NULL;

                                if (current != NULL)
                                {
                                    // attach condition
                                    if (LeftThread(current) || LeftSon(current) == NULL)
                                    {
                                        LeftSon(current) = tempR;
                                        LeftThread(current) = false;
                                        LeftSon(RightSon(node)) = LeftSon(node);
                                        LeftSon(node) = NULL;
                                        goto TraverseRightEnd;
                                    }
                                    else if (RightThread(current) || RightSon(current) == NULL)
                                    {
                                        RightSon(current) = tempR;
                                        RightThread(current) = false;
                                        LeftSon(RightSon(node)) = LeftSon(node);
                                        LeftSon(node) = NULL;
                                        goto TraverseRightEnd;
                                    }

                                    // traversal until found NULL
                                    while (current != NULL || Queue2.First != NULL)
                                    {
                                        if (LeftSon(current) != NULL && LeftThread(current) == false)
                                        {
                                            if (LeftThread(LeftSon(current)) || LeftSon(LeftSon(current)) == NULL)
                                            {
                                                LeftSon(LeftSon(current)) = tempL;
                                                LeftThread(LeftSon(current)) = false;
                                                goto TraverseRightEnd;
                                            }
                                            else if (RightThread(LeftSon(current)) || RightSon(LeftSon(current)) == NULL)
                                            {
                                                RightSon(LeftSon(current)) = tempL;
                                                RightThread(LeftSon(current)) = false;
                                                goto TraverseRightEnd;
                                            }

                                            if (LeftSon(LeftSon(current)) != NULL || RightSon(LeftSon(current)) != NULL)
                                            {
                                                enqueue(&Queue2, LeftSon(current));
                                            }
                                        }

                                        if (RightSon(current) != NULL && RightThread(current) == false)
                                        {
                                            if (LeftThread(RightSon(current)) || LeftSon(RightSon(current)) == NULL)
                                            {
                                                LeftSon(RightSon(current)) = tempL;
                                                LeftThread(RightSon(current)) = false;
                                                goto TraverseRightEnd;
                                            }
                                            else if (RightThread(RightSon(current)) || RightSon(RightSon(current)) == NULL)
                                            {
                                                RightSon(RightSon(current)) = tempL;
                                                RightThread(RightSon(current)) = tempL;
                                                goto TraverseRightEnd;
                                            }

                                            if (LeftSon(RightSon(current)) != NULL || RightSon(RightSon(current)) != NULL)
                                            {
                                                enqueue(&Queue2, RightSon(current));
                                            }
                                        }

                                        if (Queue2.First != NULL)
                                        {
                                            current = dequeue(&Queue2);
                                        }
                                        else
                                        {
                                            current = NULL;
                                        }
                                    }
                                }
                            }
                        TraverseRightEnd:
                            RightSon(nodeParent) = RightSon(node);
                            RightSon(node) = NULL;
                            free(node);
                            return node;
                        }
                        else // Jika tidak memiliki right son (thread)
                        {
                            if (successor != Root(*t))
                            {
                                successorParent = searchParent(*t, Info(successor));
                                if (successor == LeftSon(successorParent))
                                {
                                    LeftSon(successorParent) = LeftSon(successor);
                                }
                                else if (successor == RightSon(successorParent))
                                {
                                    RightSon(successorParent) = LeftSon(successor);
                                }
                                LeftSon(successor) = LeftSon(node);
                                RightSon(nodeParent) = successor;
                                LeftSon(node) = NULL;
                                free(node);
                                return node;
                            }
                            else
                            {
                                RightSon(nodeParent) = LeftSon(node);
                                LeftSon(node) = NULL;
                                free(node);
                                return node;
                            }
                        }
                    }
                }
                else
                {
                    if (Info(LeftSon(nodeParent)) == info)
                    {
                        LeftSon(nodeParent) = NULL;
                        free(node);
                        return node;
                    }
                    else
                    {
                        RightSon(nodeParent) = NULL;
                        free(node);
                        return node;
                    }
                }
            }
            else // Jika node yang dihapus merupakan root
            {
                printHalfScreen("Tidak bisa menghapus root!", true, false);
                printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
                PLATFORM_NAME == "windows" ? getch() : getchar();
                return NULL;
            }
        }

        createThread(t); // Update Thread
    }
    else
    {
        address node, nodeParent;
        node = search(*t, info);
        if (node != NULL)
        {
            nodeParent = searchParent(*t, info);
            if (LeftSon(nodeParent) != NULL && Info(LeftSon(nodeParent)) == info)
            {
                LeftSon(nodeParent) = NULL;
                free(node);
                return node;
            }
            else
            {
                RightSon(nodeParent) = NULL;
                free(node);
                return node;
            }
        }
    }
}

address deleteAVLNode(address root, infotype info){
    if(root == NULL){
        return root;
    }

    if(info < root->info){
        root->leftNode = deleteAVLNode(root->leftNode, info);
    }
    else if(info > root->info){
        root->rightNode = deleteAVLNode(root->rightNode, info);
    }
    else{
        if(root->leftNode == NULL && root->leftThread == false || root->rightNode == NULL && root->rightThread == false){
            address temp = root->leftNode ? root->leftNode : root->rightNode;
            if(temp == NULL){
                temp = root;
                root = NULL;
            }
            else{
                root = temp;
            }
            free(temp);
        }
        else{
            address temp = minValueNode(root->rightNode);
            root->info = temp->info;
            root->rightNode = deleteAVLNode(root->rightNode, temp->info);
        }
    }

    if(root == NULL){
        return root;
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

address minValueNode(address node){
    address current = node;
    while (LeftSon(current) != NULL && LeftThread(current) == false)
    {
        current = LeftSon(current);
    }
    return current;
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
        bool resmi;

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
                if (!LeftThread(current) && LeftSon(current) != NULL)
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

                if (!RightThread(current) && RightSon(current) != NULL)
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

            return NULL;
        }
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
        bool resmi;

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

bool IsEmpty(Tree t)
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

address copyNode(address Root)
{
    if (Root == NULL)
    {
        return NULL;
    }

    address newNode = allocate(Root->info);
    // recursive call
    newNode->leftNode = copyNode(Root->leftNode);
    newNode->rightNode = copyNode(Root->rightNode);

    return newNode;
}

void transform(Tree nbtree, Tree *btree)
{
    (*btree).isBinary = true;
    (*btree).isThreaded = false;
    (*btree).isAVL = false;
    (*btree).root = allocate(Info(nbtree.root));
    (*btree).root = copyNode(nbtree.root);
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

void balanceToAVL(Tree BTree, address BT, Tree *AVLTree)
{
    if (BT != NULL && (*AVLTree).isBinary == true)
    {
        (*AVLTree).root = insertAVLNode(Root(*AVLTree), Info(BT));
        PLATFORM_NAME == "windows" ? system("cls") : system("clear");
        printGridUI("Node Details", AVLTREE);
        printf("Binary Tree Asal : \n");
        PrintTree(BTree.root, 0, BTree.isBinary);
        printf("\nAVL Tree Hasil Balancing : \n");
        PrintTree(AVLTree->root, 0, AVLTree->isBinary);
        gotoxy(0, 3);
        printHalfScreen("Ketik Apapun Untuk Melanjutkan Animasi...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
        balanceToAVL(BTree, LeftSon(BT), AVLTree);
        balanceToAVL(BTree, RightSon(BT), AVLTree);
    }
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
            bool resmi;

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
            bool resmi;

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
            bool resmi;

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
    printHalfScreen("Pre order: ", true, false);
    preOrder(t, t.root);
    printHalfScreen("Post order: ", true, false);
    postOrder(t, t.root);
    printHalfScreen("In order: ", true, false);
    inOrder(t, t.root);
    printHalfScreen("Level order: ", true, false);
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

int Max(int a, int b)
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
        return 1 + Max(height(LeftThread(n) ? NULL : n->leftNode), height(RightThread(n) ? NULL : n->rightNode));
    }
}

bool isLeaf(Tree t, address n)
{
    if (t.isBinary == true)
    {
        if (((LeftThread(n) || LeftSon(n) == NULL) && (RightThread(n) || RightSon(n) == NULL)))
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
    bool resmi;
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
    bool resmi;

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
    printHalfScreen("List node :", true, false);
    listNodes(*t);
    printHalfScreen("Masukkan Info Node Yang Ingin Diupdate = ", true, false);
    scanf(" %c", &info);
    curr = search(*t, info);
    if (curr != NULL)
    {
    inputNewInfo:
        printHalfScreen("Masukkan Info Baru = ", true, false);
        scanf(" %c", &newInfo);
        if (search(*t, newInfo) == NULL)
        {
            updateNode(t, info, newInfo);
            PLATFORM_NAME == "windows" ? system("cls") : system("clear");
            printGridUI("Manipulation Menu", t->isBinary == true ? BINARYTREE : NONBINARYTREE);
            PrintTree(t->root, 0, t->isBinary);
            gotoxy(0, 4);
        }
        else
        {
            printHalfScreen("Info Node Yang Anda Input Sudah Ada! Mohon Input Info Node Yang Unik!", true, false);
            goto inputNewInfo;
        }
    }
    else
    {
        printHalfScreen("Node Tidak Ditemukan!", true, false);
        goto inputUpdatedNode;
    }
}

void updateNode(Tree *t, infotype info, infotype newInfo)
{
    Info(search(*t, info)) = newInfo;
}

void PrintTreeVisualization(Tree t, Tree btree, Tree tAVL, int treeType)
{
    if (treeType == NONBINARYTREE)
    {
        PrintTree(t.root, 0, false);
    }
    else if (treeType == BINARYTREE)
    {
        PrintTree(btree.root, 0, true);
    }
    else if (treeType == AVLTREE)
    {
        PrintTree(tAVL.root, 0, true);
    }
}

void PrintTree(address P, int Level, bool isBinary)
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

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(hConsole, c);
}

void initSystem()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    WindowsSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    WindowsSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void printGridUI(char Pesan[], int treeType)
{
    initSystem();

    printCenterLine('|', 2);
    printc(Pesan, treeType == NONBINARYTREE ? "===== \033[0;33mNon-Binary Tree\033[0m =====" : treeType == BINARYTREE ? "===== \033[0;34mBinary Tree\033[0m ====="
                                                                                                                      : "===== \033[0;32mAVL Tree\033[0m =====");
    printLine('-');
}

void printc(char JudulMenu[], char JudulTree[])
{
    int usedPos = (WindowsSize.X - strlen(JudulTree)) / 2 + 5;
    if (usedPos > 1)
    {
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        COORD cursorPos = consoleInfo.dwCursorPosition;
        gotoxy(usedPos, cursorPos.Y + 1);
    }
    printf("%s", JudulTree);

    usedPos = (WindowsSize.X - strlen(JudulMenu)) / 2;
    if (usedPos > 1)
    {
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        COORD cursorPos = consoleInfo.dwCursorPosition;
        gotoxy(usedPos, cursorPos.Y + 1);
    }
    printf("%s\n", JudulMenu);
}

void printLine(char line)
{
    int i;
    for (i = 0; i < WindowsSize.X; i++)
    {
        printf("%c", line);
    }
    printf("\n");
}

void printCenterLine(char line, int StartPos)
{
    int i;
    for (i = StartPos; i < WindowsSize.Y - 1; i++)
    {
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        gotoxy((WindowsSize.X / 2) - 2, i);
        printf("%c", line);
    }
    gotoxy(0, 0);
}

void printHalfScreen(char Pesan[], bool isNewLine, bool cancelEnter)
{
    int usedPos = (WindowsSize.X) / 2;
    if (usedPos > 1)
    {
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        int cursorPos = consoleInfo.dwCursorPosition.Y;
        if (isNewLine && !cancelEnter)
            cursorPos++;
        if (cancelEnter)
        {
            cursorPos--;
        }
        gotoxy(usedPos, cursorPos);
    }
    printf("%s", Pesan);
}