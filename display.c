#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN64) || defined(_WIN32)
#include <conio.h>
#endif
#include "header.h"
#include "includes/config.h"
#include "file.h"

void createTreeMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    int choice;
inputMenu:
    system("cls");
    printf("Selamat datang di program AVL Tree\n");
    printf("Pilih cara create tree yang diinginkan:\n");
    printf("1. Create Tree Manual\n");
    printf("2. Create Default Tree\n");
    printf("3. Load From File\n");
    printf("Pilihan: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        createTree(t);
        (*btree).isBinary = true;
        (*btree).isAVL = false;
        (*btree).root = NULL;
        (*tAVL).isBinary = true;
        (*tAVL).isAVL = true;
        (*tAVL).root = NULL;
        printf("\nPembuatan non-binary tree berhasil");
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        mainMenu(t, btree, tAVL, treeType);
        break;
    case 2:
        defaultTree(t);
        (*btree).isBinary = true;
        (*btree).isAVL = false;
        (*btree).root = NULL;
        (*tAVL).isBinary = true;
        (*tAVL).isAVL = true;
        (*tAVL).root = NULL;
        printf("\nPembuatan non-binary tree dengan nodes default berhasil");
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        mainMenu(t, btree, tAVL, treeType);
        break;
    case 3:
        char filename[] = DEFAULT_TREE_FILE;
        loadNodesTree(filename, t);
        (*btree).isBinary = true;
        (*btree).isAVL = false;
        (*btree).root = NULL;
        (*tAVL).isBinary = true;
        (*tAVL).isAVL = true;
        (*tAVL).root = NULL;
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getchar() : getchar();
        mainMenu(t, btree, tAVL, treeType);
        break;
    default:
        printf("\nInput yang anda masukkan salah! Mohon input angka 1-2");
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    }
}

void mainMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    int choice;
inputMenu:
    system("cls");
    printf("===== ");
    if (*treeType == NONBINARYTREE)
    {
        printf("Non-Binary Tree");
    }
    else if (*treeType == BINARYTREE)
    {
        printf("Binary Tree");
    }
    else if (*treeType == AVLTREE)
    {
        printf("AVL Tree");
    }
    printf(" =====\n");
    printf("\nSelamat datang di program AVL Tree\n");

    printf("Silahkan Pilih Menu yang diinginkan\n");
    printf("1. Manipulasi Tree\n");
    printf("2. Informasi Tree\n");
    printf("3. Save Tree to File\n");
    printf("4. Create New Tree\n");
    if (*treeType > NONBINARYTREE)
    {
        printf("5. Rollback Tree\n");
    }
    printf("99. Exit\n");
    printf("Pilihan: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        manipulationMenu(t, btree, tAVL, treeType);
        break;
    case 2:
        informationMenu(t, btree, tAVL, treeType);
        break;
    case 3:
        char filename[100];
        printf("Masukkan nama file (tekan enter untuk menyimpan ke default file): ");
        fgets(filename, 100, stdin);
        saveNodesTree(filename, *t, Root(*t));
        break;
    case 4:
    confirmation:
        printf("Apakah kamu yakin untuk membuat tree baru? ini akan menghapus tree yang sudah ada!\n");
        printf("Ketik y untuk ya dan n untuk tidak");
        if ((PLATFORM_NAME == "windows" ? getch() : getchar()) == 'y')
        {
            createTreeMenu(t, btree, tAVL, treeType);
        }
        else if ((PLATFORM_NAME == "windows" ? getch() : getchar()) == 'n')
        {
            goto inputMenu;
        }
        else
        {
            printf("\nInput yang anda masukkan salah! Mohon input y atau n");
            goto confirmation;
        }
        break;
    case 5:
        if (treeType > NONBINARYTREE)
        {
            switchTreeMenu(t, btree, tAVL, treeType);
        }
        else
        {
            printf("\nInput yang anda masukkan salah! Mohon input sesuai opsi menu!");
            printf("\nKetik apapun untuk melanjutkan...");
            PLATFORM_NAME == "windows" ? getch() : getchar();
            goto inputMenu;
        }
        break;
    case 99:
        exit(0);
        break;
    default:
        printf("\nInput yang anda masukkan salah! Mohon input sesuai opsi menu!");
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    }
}

void manipulationMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    int choice;
inputMenu:
    system("cls");
    printf("\nSelamat datang di program AVL Tree\n");
    printf("Silahkan Pilih Menu yang diinginkan\n");
    printf("1. Insert Node\n");
    printf("2. Delete Node\n");
    printf("3. Update Node\n");
    printf("4. Back to Main Menu\n");
    printf("Pilihan: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        if (*treeType == NONBINARYTREE)
        {
            insert(t);
        }
        else if (*treeType == BINARYTREE)
        {
            insert(btree);
        }
        else
        {
            insert(tAVL);
        }
        printf("\nNode berhasil dimasukkan!");
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    case 2:
        if (*treeType == NONBINARYTREE)
        {
            delete(t);
        }
        else if (*treeType == BINARYTREE)
        {
            delete(btree);
        }
        else
        {
            delete(tAVL);
        }
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    case 3:
        if (*treeType == NONBINARYTREE)
        {
            update(t);
        }
        else if (*treeType == BINARYTREE)
        {
            update(btree);
        }
        else
        {
            update(tAVL);
        }
        printf("\nNode berhasil diupdate!");
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    case 4:
        mainMenu(t, btree, tAVL, treeType);
        break;
    default:
        printf("\nInput yang anda masukkan salah! Mohon input angka 1-4");
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    }
}

void informationMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    int choice;
inputMenu:
    system("cls");
    printf("\nSelamat datang di program AVL Tree\n");
    printf("Silahkan Pilih Menu yang diinginkan\n");
    printf("1. Transform\n");
    printf("2. Traverse\n");
    printf("3. Print Tree Visualization\n");
    printf("4. Tree Details\n");
    printf("5. Back to Main Menu\n");
    printf("Pilihan: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        transformMenu(t, btree, tAVL, treeType);
        break;
    case 2:
        traverseMenu(t, btree, tAVL, treeType);
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    case 3:
        if (*treeType == NONBINARYTREE)
        {
            PrintTree(Root(*t), 0, (*t).isBinary);
        }
        else if (*treeType == BINARYTREE)
        {
            PrintTree(Root(*btree), 0, (*btree).isBinary);
        }
        else
        {
            PrintTree(Root(*tAVL), 0, (*tAVL).isBinary);
        }
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    case 4:
        if (*treeType == NONBINARYTREE)
        {
            showTreeDetails(t, treeType);
        }
        else if (*treeType == BINARYTREE)
        {
            showTreeDetails(btree, treeType);
        }
        else
        {
            showTreeDetails(tAVL, treeType);
        }
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    case 5:
        mainMenu(t, btree, tAVL, treeType);
        break;
    default:
        printf("\nInput yang anda masukkan salah! Mohon input angka 1-5");
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    }
}

void transformMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    int choice;
    if (*treeType == NONBINARYTREE)
    {
        printf("Akan dilakukan transformasi dari Non-Binary Tree ke Binary Tree\n1. Melanjutkan\n2. Kembali\nPilihanmu = ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            transform(*t, btree);
            printf("\nTransformasi Non-Binary tree ke Binary Tree berhasil!");
            *treeType = BINARYTREE;
        }
        else if (choice == 2)
        {
            informationMenu(t, btree, tAVL, treeType);
        }
        else
        {
            printf("\nInput yang anda masukkan salah! Mohon input 1 atau 2");
        }
    }
    else if (*treeType == BINARYTREE)
    {
        printf("Akan dilakukan balancing dari Binary Tree ke AVL Tree\n1. Melanjutkan\n2. Kembali\nPilihanmu = ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            tAVL->root = NULL; //delete the previous AVL tree
            tAVL->isBinary = true;
            balanceToAVL(btree->root, tAVL);
            printf("\nBalancing Binary Tree ke AVL Tree berhasil!");
            *treeType = AVLTREE;
        }
        else if (choice == 2)
        {
            informationMenu(t, btree, tAVL, treeType);
        }
        else
        {
            printf("\nInput yang anda masukkan salah! Mohon input 1 atau 2");
            informationMenu(t, btree, tAVL, treeType);
        }
    }
    else
    {
        printf("\nTidak dapat dilakukan transformasi lagi, kembali ke menu utama untuk kembali ke Non-Binary Tree atau Binary Tree");
    }
    printf("\nKetik apapun untuk melanjutkan...");
    PLATFORM_NAME == "windows" ? getch() : getchar();
    mainMenu(t, btree, tAVL, treeType);
}

void traverseMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    system("cls");
    if (*treeType == NONBINARYTREE)
    {
        printf("\n=== Traversal Non Binary Tree ===\n");
        traverse(*t);
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
    }
    else if (*treeType == BINARYTREE)
    {
        printf("\n=== Traversal Binary Tree ===\n");
        traverse(*btree);
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
    }
    else if (*treeType == AVLTREE)
    {
        printf("\n=== Traversal AVL Tree ===\n");
        traverse(*tAVL);
        printf("\nKetik apapun untuk melanjutkan...");
        PLATFORM_NAME == "windows" ? getch() : getchar();
    }
    informationMenu(t, btree, tAVL, treeType);
}

void switchTreeMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    int choice;
    if (*treeType == BINARYTREE)
    {
    invalidInput:
        printf("Akan dilakukan switch kembali ke Non-Binary Tree sebelum dilakukan transformasi\n1. Melanjutkan\n2. Kembali\nPilihanmu = ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("\nSwitch ke non-binary tree berhasil!");
            *treeType = NONBINARYTREE;
        }
        else if (choice == 2)
        {
            mainMenu(t, btree, tAVL, treeType);
        }
        else
        {
            printf("\nInput yang anda masukkan salah! Mohon input 1 atau 2");
            printf("\nKetik apapun untuk melanjutkan...");
            PLATFORM_NAME == "windows" ? getch() : getchar();
            goto invalidInput;
        }
        mainMenu(t, btree, tAVL, treeType);
    }
    else if (*treeType == AVLTREE)
    {
    input:
        printf("Silahkan pilih mau switch ke Tree mana. (switch ini akan kembali ke bentuk dan state tree sebelumnya sebelum dilakukan transformasi/balancing)\n");
        printf("1. Non-Binary Tree\n2. Binary Tree\n3. Kembali ke main menu\nPilihanmu = ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("\nSwitch ke non-binary berhasil!");
            *treeType = NONBINARYTREE;
        }
        else if (choice == 2)
        {
            printf("\nSwitch ke binary tree berhasil!");
            *treeType = BINARYTREE;
        }
        else if (choice == 3)
        {
            mainMenu(t, btree, tAVL, treeType);
        }
        else
        {
            printf("\nInput yang anda masukkan salah! Mohon input 1-3");
            printf("\nKetik apapun untuk melanjutkan...");
            PLATFORM_NAME == "windows" ? getch() : getchar();
            goto input;
        }
        mainMenu(t, btree, tAVL, treeType);
    }
}

void showTreeDetails(Tree *t, int *treeType)
{
    char choice;
    infotype info;
    address node;

inputMenu:
    system("cls");
    printf("=== Tree Details ===\n");
    printf("Tree Type: ");
    if (*treeType == NONBINARYTREE)
    {
        printf("Non-Binary Tree\n");
    }
    else if (*treeType == BINARYTREE)
    {
        printf("Binary Tree\n");
    }
    else if (*treeType == AVLTREE)
    {
        printf("AVL Tree\n");
    }
    printf("Node count: ");
    printf("%d\n", nodeAmount(*t));

    printf("Leaf Node count: ");
    printf("%d\n", leafAmount(*t));

    printf("Depth: ");
    printf("%d\n", depth(*t));

    printf("Print Detail Node? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y')
    {
    inputNode:
        system("cls");
        printf("Masukkan value dari node yang ingin dicari: ");
        scanf(" %c", &info);
        node = search(*t, info);

        if (node != NULL)
        {
            printf("Node value: %c\n", Info(node));
            if (node == Root(*t))
            {
                printf("Node parent: NULL (Root node)\n");
            }
            else
            {
                printf("Node parent: %c\n", Info(searchParent(*t, Info(node))));
            }
            if (*treeType != NONBINARYTREE)
            {
                printf("Height: %d\n", height(node) - 1);
            }
            printf("Level: %d\n", level(*t, Info(node)));
            printf("Leaf: ");
            if (isLeaf(*t, node))
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
        }
        else
        {
            printf("Node tidak ditemukan!\n");
        }
        printf("Apakah anda ingin mencari node yang lain? (y/n)");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y')
        {
            goto inputNode;
        }
    }
}