// fig12_04.c
// Creating and traversing a binary tree 
// preorder, inorder, and postorder
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// self-referential structure                            
struct treeNode {
    struct treeNode* leftPtr; // pointer to left subtree   
    char* data; // node value                                
    struct treeNode* rightPtr; // pointer to right subtree 
};

typedef struct treeNode TreeNode; // synonym for struct treeNode
typedef TreeNode* TreeNodePtr; // synonym for TreeNode *

// prototypes
void insertNode(TreeNodePtr* treePtr, char* value);
void inOrder(TreeNodePtr treePtr);
void preOrder(TreeNodePtr treePtr);
void postOrder(TreeNodePtr treePtr);

int main(void) {
    TreeNodePtr rootPtr = NULL; // tree initially empty

    srand(time(NULL));
    puts("Enter a sentence:");
    /*
    // insert random values between 0 and 14 in the tree
    for (int i = 1; i <= 10; ++i) {
        int item = rand() % 15;
        printf("%3d", item);
        insertNode(&rootPtr, item);
    }
    */
    // k e c f a l n g b
    // 改成token
    char word[45]; // 字元陣列
    scanf("%44[^\n]", word); // 避免空白被截斷

    char* tokens[50]; // 字串指標陣列
    char* element = strtok(word, " ");
    int token_count = 0;
    while (element != NULL) {
        tokens[token_count++] = element;
        element = strtok(NULL, " "); // 下一個
    }
    // 遍歷字元
    for (int i = 0; i < token_count; i++) {
        insertNode(&rootPtr, tokens[i]);
    }
    
    
    // traverse the tree preOrder
    puts("\n\nThe preOrder traversal is:");
    preOrder(rootPtr);

    // traverse the tree inOrder
    puts("\n\nThe inOrder traversal is:");
    inOrder(rootPtr);

    // traverse the tree postOrder
    puts("\n\nThe postOrder traversal is:");
    postOrder(rootPtr);
}

void insertNode(TreeNodePtr* treePtr, char* value) {
    if (*treePtr == NULL) { // 如果樹為空
        *treePtr = malloc(sizeof(TreeNode));
        if (*treePtr != NULL) {
            (*treePtr)->data = value;
            (*treePtr)->leftPtr = NULL;
            (*treePtr)->rightPtr = NULL;
        }
        else {
            printf("%s not inserted. No memory available.\n", value);
        }
    }
    else { // 樹不為空
     // 使用 strcmp 比較字串
        int cmp = strcmp(value, (*treePtr)->data);
        if (cmp < 0) { // value 小於當前節點
            insertNode(&((*treePtr)->leftPtr), value);
        }
        else if (cmp > 0) { // value 大於當前節點
            insertNode(&((*treePtr)->rightPtr), value);
        }
        else { // 相等，忽略重複
            printf("%s", "dup");
        }
    }
}

// begin inorder traversal of tree
void inOrder(TreeNodePtr treePtr) {
    // if tree is not empty, then traverse
    if (treePtr != NULL) {
        inOrder(treePtr->leftPtr);
        printf("%s ", treePtr->data);
        inOrder(treePtr->rightPtr);
    }
}

// begin preorder traversal of tree
void preOrder(TreeNodePtr treePtr) {
    // if tree is not empty, then traverse
    if (treePtr != NULL) {
        printf("%s ", treePtr->data);
        preOrder(treePtr->leftPtr);
        preOrder(treePtr->rightPtr);
    }
}

// begin postorder traversal of tree
void postOrder(TreeNodePtr treePtr) {
    // if tree is not empty, then traverse
    if (treePtr != NULL) {
        postOrder(treePtr->leftPtr);
        postOrder(treePtr->rightPtr);
        printf("%s ", treePtr->data);
    }
}



/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/