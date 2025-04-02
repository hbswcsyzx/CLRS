// Exercise 10.2-6
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 定义双向链表节点结构
typedef struct Node
{
    int key;
    struct Node *np; // 存储下一个节点和前一个节点的异或结果
} Node;

// 定义链表结构，包含头节点和尾节点指针
typedef struct List
{
    Node *head;
    Node *tail;
} List;

// 定义搜索结果结构，包含当前节点和前一个节点
typedef struct
{
    Node *current;
    Node *previous;
} SearchResult;

// LIST - SEARCH 实现
SearchResult LIST_SEARCH(List *L, int k)
{
    Node *current = L->head;
    Node *previous = NULL;
    while (current != NULL)
    {
        if (current->key == k)
        {
            SearchResult res = {current, previous};
            return res;
        }
        else
        {
            Node *successor = (Node *)((uintptr_t)current->np ^ (uintptr_t)previous);
            previous = current;
            current = successor;
        }
    }
    SearchResult res = {NULL, NULL};
    return res;
}

// LIST - PREPEND 实现
void LIST_PREPEND(List *L, Node *x)
{
    x->np = L->head;
    if (L->head != NULL)
    {
        L->head->np = (Node *)((uintptr_t)L->head->np ^ (uintptr_t)x);
    }
    else
    {
        L->tail = x;
    }
    L->head = x;
}

// LIST - INSERT 实现
void LIST_INSERT(List *L, Node *x, Node *y, Node *previous)
{
    Node *successor = (Node *)((uintptr_t)y->np ^ (uintptr_t)previous);
    x->np = (Node *)((uintptr_t)y ^ (uintptr_t)successor);
    y->np = (Node *)((uintptr_t)y->np ^ (uintptr_t)successor ^ (uintptr_t)x);
    if (successor != NULL)
    {
        successor->np = (Node *)((uintptr_t)successor->np ^ (uintptr_t)y ^ (uintptr_t)x);
    }
    if (y == L->tail)
    {
        L->tail = x;
    }
}

// LIST - DELETE 实现
void LIST_DELETE(List *L, Node *x, Node *previous)
{
    if (previous == NULL)
    {
        L->head = x->np;
        if (L->head == NULL)
        {
            L->tail = NULL;
        }
        else
        {
            L->head->np = (Node *)((uintptr_t)L->head->np ^ (uintptr_t)x);
        }
    }
    else
    {
        Node *successor = (Node *)((uintptr_t)x->np ^ (uintptr_t)previous);
        previous->np = (Node *)((uintptr_t)previous->np ^ (uintptr_t)x ^ (uintptr_t)successor);
        if (successor == NULL)
        {
            L->tail = previous;
        }
        else
        {
            successor->np = (Node *)((uintptr_t)successor->np ^ (uintptr_t)x ^ (uintptr_t)previous);
        }
    }
}

// LIST - REVERSE 实现
void LIST_REVERSE(List *L)
{
    Node *prev = NULL;
    Node *current = L->head;
    L->tail = L->head; // 先将尾指针指向原头节点
    while (current != NULL)
    {
        Node *next = (Node *)((uintptr_t)current->np ^ (uintptr_t)prev);
        // 交换当前节点的前后关系（更新 np 指针）
        current->np = (Node *)((uintptr_t)prev ^ (uintptr_t)next);
        prev = current;
        current = next;
    }
    L->head = prev; // 最终 prev 指向原尾节点，设为新头节点
}

// 辅助函数：打印链表
void print_list(List *L)
{
    Node *current = L->head;
    Node *prev = NULL;
    Node *next;
    printf("List: ");
    while (current != NULL)
    {
        printf("%d ", current->key);
        next = (Node *)((uintptr_t)current->np ^ (uintptr_t)prev);
        prev = current;
        current = next;
    }
    printf("\n");
}

int main()
{
    List L = {NULL, NULL};

    // 测试 LIST_PREPEND
    Node *n1 = (Node *)malloc(sizeof(Node));
    n1->key = 1;
    LIST_PREPEND(&L, n1);

    Node *n2 = (Node *)malloc(sizeof(Node));
    n2->key = 2;
    LIST_PREPEND(&L, n2);

    Node *n3 = (Node *)malloc(sizeof(Node));
    n3->key = 3;
    LIST_PREPEND(&L, n3);

    print_list(&L); // 预期输出: 3 2 1

    // 测试 LIST_SEARCH
    SearchResult res = LIST_SEARCH(&L, 2);
    if (res.current != NULL)
    {
        printf("Found key %d, previous key %d\n", res.current->key, res.previous != NULL ? res.previous->key : -1);
    }
    else
    {
        printf("Not found\n");
    }

    // 测试 LIST_INSERT
    Node *n4 = (Node *)malloc(sizeof(Node));
    n4->key = 4;
    LIST_INSERT(&L, n4, n2, res.previous);
    print_list(&L); // 预期输出: 3 2 4 1

    // 测试 LIST_DELETE
    LIST_DELETE(&L, n2, res.previous);
    print_list(&L); // 预期输出: 3 4 1

    // 测试 LIST_REVERSE
    LIST_REVERSE(&L);
    print_list(&L); // 预期输出: 1 4 3

    // 清理内存
    Node *current = L.head;
    Node *prev = NULL;
    Node *next;
    while (current != NULL)
    {
        next = (Node *)((uintptr_t)current->np ^ (uintptr_t)prev);
        prev = current;
        free(current);
        current = next;
    }

    return 0;
}