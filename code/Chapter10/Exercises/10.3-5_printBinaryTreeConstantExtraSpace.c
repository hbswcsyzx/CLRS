// Exercise 10.3-5
#include <stdio.h>
#include <stdlib.h>

// Define the binary tree node structure
typedef struct BinaryTreeNode
{
    int key;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
    struct BinaryTreeNode *p; // parent pointer
} BinaryTreeNode;

// Define the binary tree structure
typedef struct BinaryTree
{
    BinaryTreeNode *root;
} BinaryTree;

// Function to print binary tree with constant extra space (preorder)
void printBinaryTreeConstantExtraSpace(BinaryTree *T)
{
    BinaryTreeNode *x = T->root;
    BinaryTreeNode *y = NULL;
    while (x != NULL)
    {
        BinaryTreeNode *z = x;
        if (x->p == y)
        {
            printf("%d ", x->key);
            if (x->left != NULL)
            {
                x = x->left;
            }
            else if (x->right != NULL)
            {
                x = x->right;
            }
            else
            {
                x = x->p;
            }
        }
        else if (x->left == y && x->right != NULL)
        {
            x = x->right;
        }
        else
        {
            x = x->p;
        }
        y = z;
    }
}

// Helper function to create a new node
BinaryTreeNode *createNode(int key)
{
    BinaryTreeNode *newNode = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->p = NULL;
    return newNode;
}

// Example usage
int main()
{
    BinaryTree T;
    BinaryTreeNode *root = createNode(1);
    BinaryTreeNode *leftChild = createNode(2);
    BinaryTreeNode *rightChild = createNode(3);

    root->left = leftChild;
    root->right = rightChild;
    leftChild->p = root;
    rightChild->p = root;

    T.root = root;

    printf("Preorder traversal: ");
    printBinaryTreeConstantExtraSpace(&T);
    printf("\n");

    // Clean up memory (simplified, add more if needed)
    free(leftChild);
    free(rightChild);
    free(root);

    return 0;
}