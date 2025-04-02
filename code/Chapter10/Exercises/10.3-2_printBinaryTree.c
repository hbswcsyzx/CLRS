// Exercise 10.3-2
#include <stdio.h>

typedef struct BinaryTreeNode
{
    int key;
    struct BinaryTreeNode *left_child;
    struct BinaryTreeNode *right_child;
} BinaryTreeNode;

void printBinaryTree(BinaryTreeNode *x)
{
    if (x != NULL)
    {
        printBinaryTree(x->left_child);
        printf("%d ", x->key);
        printBinaryTree(x->right_child);
    }
}