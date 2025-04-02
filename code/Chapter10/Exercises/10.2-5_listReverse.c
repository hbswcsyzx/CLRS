// Exercise 10.2-5
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct ListNode
{
    int data;
    struct ListNode *next;
} ListNode;

// 定义链表结构
typedef struct
{
    ListNode *head;
} List;

// 初始化链表
List *createList()
{
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;
    return l;
}

// 创建新节点
ListNode *createNode(int data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;
    return node;
}

// 反转链表函数
void listReverse(List *L)
{
    ListNode *previous = NULL;
    ListNode *current = L->head;
    while (current != NULL)
    {
        ListNode *successor = current->next;
        current->next = previous;
        previous = current;
        current = successor;
    }
    L->head = previous;
}

// 打印链表
void printList(List *L)
{
    ListNode *node = L->head;
    while (node != NULL)
    {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// 测试代码
int main()
{
    List *l = createList();
    // 构建链表 1 -> 2 -> 3 -> 4
    l->head = createNode(1);
    l->head->next = createNode(2);
    l->head->next->next = createNode(3);
    l->head->next->next->next = createNode(4);

    printf("Original list: ");
    printList(l);

    listReverse(l);

    printf("Reversed list: ");
    printList(l);

    // 释放链表内存（简单示例，实际可优化）
    ListNode *current = l->head;
    while (current != NULL)
    {
        ListNode *next = current->next;
        free(current);
        current = next;
    }
    free(l);

    return 0;
}