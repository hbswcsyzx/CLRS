// Exercise 10.3-3
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构体
typedef struct BinaryTreeNode
{
    int key;
    struct BinaryTreeNode *left_child;
    struct BinaryTreeNode *right_child;
} BinaryTreeNode;

// 定义栈节点结构体
typedef struct StackNode
{
    BinaryTreeNode *data;
    struct StackNode *next;
} StackNode;

// 创建栈节点
StackNode *createStackNode(BinaryTreeNode *node)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->data = node;
    newNode->next = NULL;
    return newNode;
}

// 检查栈是否为空
int isEmpty(StackNode *S)
{
    return S == NULL;
}

// 入栈操作
void push(StackNode **S, BinaryTreeNode *x)
{
    StackNode *newNode = createStackNode(x);
    newNode->next = *S;
    *S = newNode;
}

// 出栈操作
BinaryTreeNode *pop(StackNode **S)
{
    if (isEmpty(*S))
        return NULL;
    StackNode *temp = *S;
    *S = (*S)->next;
    BinaryTreeNode *data = temp->data;
    free(temp);
    return data;
}

// 非递归中序遍历打印二叉树函数
void PRINT_BINARY_TREE_NONRECURSIVE(BinaryTreeNode *T)
{
    StackNode *S = NULL;
    BinaryTreeNode *x = T;
    while (x != NULL)
    {
        push(&S, x);
        x = x->left_child; // 调整为left_child
    }
    while (!isEmpty(S))
    {
        x = pop(&S);
        printf("%d ", x->key);
        x = x->right_child; // 调整为right_child
        while (x != NULL)
        {
            push(&S, x);
            x = x->left_child; // 调整为left_child
        }
    }
}