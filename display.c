#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_WIN64) || defined(_WIN32)
#include <conio.h>
#endif
#include "header.h"
#include "includes/config.h"
#include "file.h"

void createTreeMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    int choice;
    char confirm;
    char filename[30];
inputMenu:
    *treeType = NONBINARYTREE;
    system("cls");
    printGridUI("Create Tree Menu", *treeType);

    gotoxy(0, 4);
    printHalfScreen("Selamat datang di program AVL Tree", false, false);
    printHalfScreen("Pilih cara create tree yang diinginkan:", true, false);
    printHalfScreen("1. Create Tree Manual", true, false);
    printHalfScreen("2. Create Default Tree", true, false);
    printHalfScreen("3. Load From File", true, false);
    printHalfScreen("Pilihan: ", true, false);
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        createTree(t);
        (*btree).isBinary = true;
        (*btree).isThreaded = false;
        (*btree).isAVL = false;
        (*btree).root = NULL;
        (*tAVL).isBinary = true;
        (*tAVL).isThreaded = false;
        (*tAVL).isAVL = true;
        (*tAVL).root = NULL;
        
        printHalfScreen("Pembuatan non-binary tree secara manual berhasil", true, false);
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
        mainMenu(t, btree, tAVL, treeType);
        break;
    case 2:
        gotoxy(0, 4);
        PrintDefaultTreePreview();
        gotoxy(0, 10);
        printHalfScreen("Akan dibuat Non-Binary Tree dengan nilai default seperti visualisasi di samping.", true, false);
        printHalfScreen("input y untuk konfirmasi: ", true, false);
        scanf(" %c", &confirm);
        if(confirm != 'y'){
            printHalfScreen("Pembuatan default tree dibatalkan!", true, false);
            printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
            PLATFORM_NAME == "windows" ? getch() : getchar();
            goto inputMenu;
        }else{ 
            defaultTree(t);
            (*btree).isBinary = true;
            (*btree).isThreaded = false;
            (*btree).isAVL = false;
            (*btree).root = NULL;
            (*tAVL).isBinary = true;
            (*tAVL).isThreaded = false;
            (*tAVL).isAVL = true;
            (*tAVL).root = NULL;
            printHalfScreen("Pembuatan non-binary tree dengan nodes default berhasil", true, false);
            printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
            PLATFORM_NAME == "windows" ? getch() : getchar();
            mainMenu(t, btree, tAVL, treeType);
        }
        break;
    case 3:
        printHalfScreen("Masukkan nama file (tekan enter untuk memuat dari default file): ", true, false);
        getchar();
        fgets(filename, 30, stdin);
        filename[strcspn(filename, "\r\n")] = 0; // remove newline
        loadNodesTree(filename, t);
        (*btree).isBinary = true;
        (*btree).isAVL = false;
        (*btree).root = NULL;
        (*tAVL).isBinary = true;
        (*tAVL).isAVL = true;
        (*tAVL).root = NULL;
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
        mainMenu(t, btree, tAVL, treeType);
        break;
    default:
        printHalfScreen("Input yang anda masukkan salah! Mohon input angka 1-3", true, false);
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    }
}

void mainMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    int choice;
    char filename[30];
inputMenu:
    PLATFORM_NAME == "windows" ? system("cls") : system("clear");
    printGridUI("Main Menu", *treeType);
    PrintTreeVisualization(*t, *btree, *tAVL, *treeType);

    gotoxy(0, 4);
    printHalfScreen("Selamat datang di program transformasi", false, false);
    printHalfScreen("Non-Binary Tree ke AVL Tree!", true, false);
    printHalfScreen("Silahkan pilih beberapa opsi fitur berikut:", true, false);
    printHalfScreen("1. Manipulasi Tree", true, false);
    printHalfScreen("2. Informasi Tree", true, false);
    printHalfScreen("3. Save Tree to File", true, false);
    printHalfScreen("4. Create New Tree", true, false);
    if (*treeType > NONBINARYTREE)
    {
        printHalfScreen("5. Rollback Tree", true, false);
    }
    printHalfScreen("99. Exit", true, false);
    printHalfScreen("Pilihan: ", true, false);
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
        printHalfScreen("Masukkan nama file (tekan enter untuk memuat dari default file): ", true, false);
        getchar();
        fgets(filename, 30, stdin);
        filename[strcspn(filename, "\r\n")] = 0; // remove newline
        if (fileExists(filename))
        {
            char bufferMessage[200] = "\033[1;33m[WARN]\t\033[1;0mSudah Terdapat data pada file '";
            strcat(strcat(bufferMessage, filename), "'. Menyimpan pada file ini akan mengakibatkan data sebelumnya terhapus. Apakah anda akan menyimpannya? (y/n) ");
            printHalfScreen(bufferMessage, true, false);
            if ((PLATFORM_NAME == "windows" ? getchar() : getchar()) == 'y')
            {
                fclose(accessFile(filename, "w"));
                saveNodesTree(filename, *t, Root(*t));
            }
        }
        else
        {
            saveNodesTree(filename, *t, Root(*t));
        }
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        getchar();
        goto inputMenu;
        break;
    case 4:
    confirmation:
        printHalfScreen("Apakah kamu yakin untuk membuat tree baru?", true, false);
        printHalfScreen("Ini akan menghapus tree yang sudah ada!\n", true, false);
        printHalfScreen("Ketik y untuk ya dan n untuk tidak", true, false);
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
            printHalfScreen("Input yang anda masukkan salah! Mohon input y atau n", true, false);
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
            printHalfScreen("Input yang anda masukkan salah! Mohon input sesuai opsi menu!", true, false);
            printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
            PLATFORM_NAME == "windows" ? getch() : getchar();
            goto inputMenu;
        }
        break;
    case 99:
        exit(0);
        break;
    default:
        printHalfScreen("Input yang anda masukkan salah! Mohon input sesuai opsi menu!", true, false);
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    }
}

void manipulationMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    int choice;
inputMenu:
    PLATFORM_NAME == "windows" ? system("cls") : system("clear");
    printGridUI("Manipulation Menu", *treeType);
    PrintTreeVisualization(*t, *btree, *tAVL, *treeType);

    gotoxy(0, 4);
    printHalfScreen("Silahkan Pilih Menu Manipulation yang diinginkan", false, false);
    printHalfScreen("1. Insert Node", true, false);
    printHalfScreen("2. Delete Node", true, false);
    printHalfScreen("3. Update Node", true, false);
    printHalfScreen("4. Transform Tree", true, false);
    if (*treeType > NONBINARYTREE)
    {
        printHalfScreen("5. Create Thread", true, false);
    }
    printHalfScreen("99. Back to Main Menu", true, false);
    printHalfScreen("Pilihan: ", true, false);
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
            if (IsThreaded(*btree))
            {
                createThread(btree);
            }
        }
        else
        {
            insert(tAVL);
        }
        goto inputMenu;
        break;
    case 2:
        if (*treeType == NONBINARYTREE)
        {
            delete (t);
        }
        else if (*treeType == BINARYTREE)
        {
            delete (btree);
        }
        else
        {
            delete (tAVL);
        }
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
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
        printHalfScreen("Node berhasil diupdate!", false, false);
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    case 4:
        transformMenu(t, btree, tAVL, treeType);
        break;
    case 5:
        if (*treeType > NONBINARYTREE)
        {
            if (*treeType == BINARYTREE)
            {
                createThread(btree);
            }
            else if (*treeType == AVLTREE)
            {
                createThread(tAVL);
            }
            printHalfScreen("Thread berhasil dibuat!", true, false);
            printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
            getch();
            goto inputMenu;
        }
        else
        {
            printHalfScreen("Input yang anda masukkan salah! Mohon input angka 1-4", true, false);
            printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
            getch();
            goto inputMenu;
        }
        break;
    case 99:
        mainMenu(t, btree, tAVL, treeType);
        break;
    default:
        printHalfScreen("Input yang anda masukkan salah! Mohon input angka 1-4", true, false);
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
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
    printGridUI("Information Menu", *treeType);
    gotoxy(0, 4);
    PrintTreeVisualization(*t, *btree, *tAVL, *treeType); 
    gotoxy(0, 4);
    printHalfScreen("Silahkan Pilih Menu Information yang diinginkan", false, false);
    printHalfScreen("1. Traverse", true, false);
    printHalfScreen("2. Tree Details", true, false);
    printHalfScreen("3. Back to Main Menu", true, false);
    printHalfScreen("Pilihan: ", true, false);
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        traverseMenu(t, btree, tAVL, treeType);
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    case 2:
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
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
        goto inputMenu;
        break;
    case 3:
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
    
    PLATFORM_NAME == "windows" ? system("cls") : system("clear");
    printGridUI("Transform Menu", *treeType);
    PrintTreeVisualization(*t, *btree, *tAVL, *treeType);
    gotoxy(0, 4);
    if (*treeType == NONBINARYTREE)
    {
        printHalfScreen("Akan dilakukan transformasi dari Non-Binary Tree ke Binary Tree.", false, false);
        printHalfScreen("1. Melanjutkan", true, false);
        printHalfScreen("2. Kembali", true, false);
        printHalfScreen("Pilihanmu = ", true, false);
        scanf("%d", &choice);
        if (choice == 1)
        {
            transform(*t, btree);
            *treeType = BINARYTREE;
            PLATFORM_NAME == "windows" ? system("cls") : system("clear");
            printGridUI("Transform Menu", *treeType);
            printf("Tree Non-Binary Asal : \n");
            PrintTree(t->root, 0, t->isBinary);
            printf("\nTree Binary Hasil : \n");
            PrintTreeVisualization(*t, *btree, *tAVL, *treeType);
            gotoxy(0, 4);
            printHalfScreen("Transformasi Non-Binary tree ke Binary Tree berhasil!", false, false);
        }
        else if (choice == 2)
        {
            informationMenu(t, btree, tAVL, treeType);
        }
        else
        {
            printHalfScreen("Input yang anda masukkan salah! Mohon input 1 atau 2", true, false);
        }
    }
    else if (*treeType == BINARYTREE)
    {
        printHalfScreen("Akan dilakukan transformasi dari Binary Tree ke AVL Tree.", false, false);
        printHalfScreen("1. Melanjutkan", true, false);
        printHalfScreen("2. Kembali", true, false);
        printHalfScreen("Pilihanmu = ", true, false);
        scanf("%d", &choice);
        if (choice == 1)
        {
            tAVL->root = NULL; //delete the previous AVL tree
            tAVL->isBinary = true;
            balanceToAVL(*btree, btree->root, tAVL);
            *treeType = AVLTREE;
            PLATFORM_NAME == "windows" ? system("cls") : system("clear");
            printGridUI("Transform Menu", *treeType);
            printf("Tree Binary Asal : \n");
            PrintTree(btree->root, 0, btree->isBinary);
            printf("\nTree AVL Hasil : \n");
            PrintTreeVisualization(*t, *btree, *tAVL, *treeType);
            gotoxy(0, 4);
            printHalfScreen("Balancing Binary Tree ke AVL Tree berhasil!", false, false);
        }
        else if (choice == 2)
        {
            manipulationMenu(t, btree, tAVL, treeType);
        }
        else
        {
            printHalfScreen("Input yang anda masukkan salah! Mohon input 1 atau 2", true, false);
            manipulationMenu(t, btree, tAVL, treeType);
        }
    }
    else
    {
        printHalfScreen("Tidak dapat dilakukan transformasi lagi, kembali ke menu utama untuk kembali ke Non-Binary Tree atau Binary Tree", true, false);
    }
    printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
    PLATFORM_NAME == "windows" ? getch() : getchar();
    mainMenu(t, btree, tAVL, treeType);
}

void traverseMenu(Tree *t, Tree *btree, Tree *tAVL, int *treeType)
{
    if (*treeType == NONBINARYTREE)
    {
        printHalfScreen("=== Traversal Non Binary Tree ===", true, false);
        traverse(*t);
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
    }
    else if (*treeType == BINARYTREE)
    {
        printHalfScreen("=== Traversal Binary Tree ===", true, false);
        traverse(*btree);
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
        PLATFORM_NAME == "windows" ? getch() : getchar();
    }
    else if (*treeType == AVLTREE)
    {
        printHalfScreen("=== Traversal AVL Tree ===", true, false);
        traverse(*tAVL);
        printHalfScreen("Ketik apapun untuk melanjutkan...", true, false);
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
        printHalfScreen("(Rollback akan kembali ke bentuk dan state tree sebelumnya)", true, false);
        printHalfScreen("Akan dilakukan Rollback ke Non-Binary Tree sebelum dilakukan transformasi", true, false);
        printHalfScreen("1. Melanjutkan", true, false);
        printHalfScreen("2. Kembali", true, false);
        printHalfScreen("Pilihanmu = ", true, false);
        scanf("%d", &choice);
        if (choice == 1)
        {
            printHalfScreen("\nSwitch ke non-binary tree berhasil!", true, false);
            *treeType = NONBINARYTREE;
        }
        else if (choice == 2)
        {
            mainMenu(t, btree, tAVL, treeType);
        }
        else
        {
            printHalfScreen("\nInput yang anda masukkan salah! Mohon input 1 atau 2", true, false);
            printHalfScreen("\nKetik apapun untuk melanjutkan...", true, false);
            PLATFORM_NAME == "windows" ? getch() : getchar();
            goto invalidInput;
        }
        mainMenu(t, btree, tAVL, treeType);
    }
    else if (*treeType == AVLTREE)
    {
    input:
        printHalfScreen("(Rollback akan kembali ke bentuk dan state tree sebelumnya)", true, false);
        printHalfScreen("Silahkan pilih jenis tree untuk dilakukan Rollback.", true, false);
        printHalfScreen("1. Non-Binary Tree", true, false);
        printHalfScreen("2. Binary Tree", true, false);
        printHalfScreen("3. Kembali ke main menu", true, false);
        printHalfScreen("Pilihanmu = ", true, false);
        scanf("%d", &choice);
        if (choice == 1)
        {
            printHalfScreen("Switch ke non-binary berhasil!", true, false);
            *treeType = NONBINARYTREE;
        }
        else if (choice == 2)
        {
            printHalfScreen("Switch ke binary tree berhasil!", true, false);
            *treeType = BINARYTREE;
        }
        else if (choice == 3)
        {
            mainMenu(t, btree, tAVL, treeType);
        }
        else
        {
            printHalfScreen("\nInput yang anda masukkan salah! Mohon input 1-3", true, false);
            printHalfScreen("\nKetik apapun untuk melanjutkan...", true, false);
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
    PLATFORM_NAME == "windows" ? system("cls") : system("clear");
    printGridUI("Tree Details", *treeType);
    PrintTree(t->root, 0, t->isBinary);
    gotoxy(0, 3);
    printHalfScreen("Tree Type: ", true, false);
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

    if (*treeType > NONBINARYTREE)
    {
        if (IsThreaded(*t))
        {
            printHalfScreen("Threaded Tree: Yes", true, false);
        }
        else
        {
            printHalfScreen("Threaded Tree: No", true, false);
        }
    }
    printHalfScreen("Node count: ", true, false);
    printf("%d", nodeAmount(*t));

    printHalfScreen("Leaf Node count: ", true, false);
    printf("%d", leafAmount(*t));

    printHalfScreen("Depth: ", true, false);
    printf("%d", depth(*t));

    printHalfScreen("Print Detail Node? (y/n): ", true, false);
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y')
    {
    inputNode:
        PLATFORM_NAME == "windows" ? system("cls") : system("clear");
        printGridUI("Node Details", *treeType);
        PrintTree(t->root, 0, t->isBinary);
        gotoxy(0, 3);
        printHalfScreen("Masukkan value dari node yang ingin dicari: ",true,false);
        scanf(" %c", &info);
        node = search(*t, info);

        if (node != NULL)
        {
            printHalfScreen("Node value: ", true, false);
            printf("%c", Info(node));
            if (node == Root(*t))
            {
                printHalfScreen("Node parent: NULL (Root node)", true, false);
            }
            else
            {
                printHalfScreen("Node parent: ",true,false);
                if(searchParent(*t, Info(node)) == NULL){
                    printf("NULL (Root node)");
                }else{
                    printf("%c", Info(searchParent(*t, Info(node))));
                
                }
            }
            printHalfScreen(IsBinary(*t) ? "Left Son: " : "First Son: ", true, false);
            if (LeftSon(node) != NULL)
            {
                printf("%c", Info(LeftSon(node)));
            }
            else
            {
                printf("NULL");
            }
            printHalfScreen(IsBinary(*t) ? "Right Son: " : "Next Brother: ", true, false);
            if (RightSon(node) != NULL)
            {
                printf("%c", Info(RightSon(node)));
            }
            else
            {
                printf("NULL");
            }
            if (*treeType > NONBINARYTREE)
            {
                printHalfScreen("Left Thread: ", true, false);
                if (LeftThread(node))
                {
                    printf("Yes");
                }
                else
                {
                    printf("No");
                }
                printHalfScreen("Right Thread: ", true, false);
                if (RightThread(node))
                {
                    printf("Yes");
                }
                else
                {
                    printf("No");
                }
            }
            if (*treeType != NONBINARYTREE)
            {
                printHalfScreen("Height: ", true, false);
                printf("%d", height(node) - 1);
            }
            printHalfScreen("Level: ", true, false);
            printf("%d", level(*t, Info(node)));
            printHalfScreen("Is Leaf: ", true, false);
            if (isLeaf(*t, node))
            {
                printf("Yes");
            }
            else
            {
                printf("No");
            }
        }
        else
        {
            printHalfScreen("Node tidak ditemukan!", true, false);
        }
        printHalfScreen("Apakah anda ingin mencari node yang lain? (y/n): ", true, false);
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y')
        {
            goto inputNode;
        }
    }
}

void showTreeTypes(int treeType)
{
    printf("===== ");
    if (treeType == NONBINARYTREE)
    {
        printf("\033[0;33mNon-Binary Tree\033[0m");
    }
    else if (treeType == BINARYTREE)
    {
        printf("\033[0;34mBinary Tree\033[0m");
    }
    else if (treeType == AVLTREE)
    {
        printf("\033[0;32mAVL Tree\033[0m");
    }
    printf(" =====");
}

void PrintDefaultTreePreview(){
    Tree t;
    defaultTree(&t);
    PrintTree(Root(t), 0, t.isBinary);
}
