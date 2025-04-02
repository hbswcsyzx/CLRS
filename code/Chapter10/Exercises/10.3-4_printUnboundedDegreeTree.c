// Exercise 10.3-4
#include <stdio.h>
#include <stdlib.h>

// 定义无界度数树节点结构
typedef struct UnboundedDegreeTreeNode
{
    int key;
    struct UnboundedDegreeTreeNode *left_child;
    struct UnboundedDegreeTreeNode *right_sibling;
} UnboundedDegreeTreeNode;

// 打印无界度数树函数
void printUnboundedDegreeTree(UnboundedDegreeTreeNode *x)
{
    if (x != NULL)
    {
        printf("%d ", x->key);
        printUnboundedDegreeTree(x->left_child);
        printUnboundedDegreeTree(x->right_sibling);
    }
}

// 辅助函数：创建新节点
UnboundedDegreeTreeNode *createNode(int key)
{
    UnboundedDegreeTreeNode *newNode = (UnboundedDegreeTreeNode *)malloc(sizeof(UnboundedDegreeTreeNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newNode->key = key;
    newNode->left_child = NULL;
    newNode->right_sibling = NULL;
    return newNode;
}

int main()
{
    // 简单构建一个无界度数树示例（此处为简化示例，可根据实际需求扩展）
    UnboundedDegreeTreeNode *root = createNode(1);
    UnboundedDegreeTreeNode *child2 = createNode(2);
    UnboundedDegreeTreeNode *child3 = createNode(3);

    root->left_child = child2;
    child2->right_sibling = child3;

    printf("打印无界度数树: ");
    printUnboundedDegreeTree(root);
    printf("\n");

    // 清理内存
    free(root->left_child->right_sibling);
    free(root->left_child);
    free(root);

    return 0;
}