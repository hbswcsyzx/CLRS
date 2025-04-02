#include <stdio.h>
#include <stdlib.h>

// Forward declaration of DLLSentinel for function pointer
typedef struct DLLSentinel DLLSentinel;

// Define the node structure
typedef struct LinkedListNode
{
    struct LinkedListNode *prev;
    struct LinkedListNode *next;
    void *data;
} LinkedListNode;

// Function pointer type for get_key function
typedef int (*GetKeyFunc)(void *);

// Identity function for get_key
int identityGetKey(void *data)
{
    return *(int *)data;
}

// Initialize a node of a circular doubly linked list with a sentinel with the given data.
LinkedListNode *linkedListNodeInit(void *data)
{
    LinkedListNode *node = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->prev = NULL;
    node->next = NULL;
    node->data = data;
    return node;
}

// Return data.
void *linkedListNodeGetData(LinkedListNode *node)
{
    return node->data;
}

// Define the circular doubly linked list with sentinel structure
typedef struct DLLSentinel
{
    LinkedListNode *sentinel;
    GetKeyFunc get_key;
} DLLSentinel;

// Initialize the sentinel of a circular doubly linked list with a sentinel.
//
// Arguments:
// get_key_func -- an optional function that returns the key for the
// objects stored. May be a static function in the object class. If
// omitted, then identity function is used.
DLLSentinel *dllSentinelInit(GetKeyFunc getKeyFunc)
{
    DLLSentinel *list = (DLLSentinel *)malloc(sizeof(DLLSentinel));
    if (list == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->sentinel = linkedListNodeInit(NULL);
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;

    if (getKeyFunc == NULL)
    {
        list->get_key = identityGetKey;
    }
    else
    {
        list->get_key = getKeyFunc;
    }
    return list;
}

// Search a circular doubly linked list with a sentinel for a node with key k.
//
// Returns:
// x -- node with key k or NULL if not found
LinkedListNode *dllSentinelSearch(DLLSentinel *list, int k)
{
    LinkedListNode *x = list->sentinel->next;
    // Go down the list until key k is found.
    // Need to test for the sentinel to avoid calling get_key(None) when x is the sentinel.
    while (x != list->sentinel && list->get_key(x->data) != k)
    {
        x = x->next;
    }

    if (x == list->sentinel)
    {                // went through the whole list?
        return NULL; // yes, so no node had key
    }
    else
    {
        return x; // found it!
    }
}

// Insert a node with data after node y.  Return the new node.
LinkedListNode *dllSentinelInsert(DLLSentinel *list, void *data, LinkedListNode *y)
{
    LinkedListNode *x = linkedListNodeInit(data);
    x->next = y->next;
    x->prev = y;
    y->next->prev = x;
    y->next = x;
    return x;
}

// Insert a node with data as the head of a circular doubly linked list with a sentinel.
// Return the new node.
LinkedListNode *dllSentinelPrepend(DLLSentinel *list, void *data)
{
    return dllSentinelInsert(list, data, list->sentinel);
}

// Append a node with data to the tail of a circular doubly linked list with a sentinel.
// Return the new node.
LinkedListNode *dllSentinelAppend(DLLSentinel *list, void *data)
{
    return dllSentinelInsert(list, data, list->sentinel->prev);
}

// Remove a node x from the a circular doubly linked list with a sentinel.
//
// Assumption:
// x is a node in the linked list.
void dllSentinelDelete(DLLSentinel *list, LinkedListNode *x)
{
    if (x == list->sentinel)
    {
        fprintf(stderr, "Cannot delete sentinel.\n");
        exit(EXIT_FAILURE);
    }
    x->prev->next = x->next;
    x->next->prev = x->prev;
    free(x);
}

// Delete all nodes in a circular doubly linked list with a sentinel.
void dllSentinelDeleteAll(DLLSentinel *list)
{
    LinkedListNode *current = list->sentinel->next;
    while (current != list->sentinel)
    {
        LinkedListNode *next = current->next;
        free(current);
        current = next;
    }
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
}

// Print the circular doubly linked list with a sentinel in a similar format as Python's __str__
void dllSentinelPrint(DLLSentinel *list)
{
    printf("[");
    LinkedListNode *x = list->sentinel->next;
    if (x != list->sentinel)
    {
        while (x->next != list->sentinel)
        {
            printf("%d, ", *(int *)x->data);
            x = x->next;
        }
        printf("%d", *(int *)x->data);
    }
    printf("]\n");
}

// Return a copy of this circular doubly linked list with a sentinel.
DLLSentinel *dllSentinelCopy(DLLSentinel *list)
{
    DLLSentinel *c = dllSentinelInit(list->get_key);
    LinkedListNode *x = list->sentinel->next;
    while (x != list->sentinel)
    {
        dllSentinelAppend(c, x->data);
        x = x->next;
    }
    return c;
}

// Free the circular doubly linked list with a sentinel memory
void dllSentinelFree(DLLSentinel *list)
{
    dllSentinelDeleteAll(list);
    free(list->sentinel);
    free(list);
}

// Simple test key object
typedef struct
{
    char *state;
    int key;
} KeyObject;

// Function to get key from KeyObject
int keyObjectGetKey(void *obj)
{
    KeyObject *kobj = (KeyObject *)obj;
    return kobj->key;
}

// Testing
int main()
{
    // Insert.
    DLLSentinel *linked_list1 = dllSentinelInit(NULL);
    for (int i = 0; i < 10; i++)
    {
        int *data = (int *)malloc(sizeof(int));
        *data = i;
        dllSentinelPrepend(linked_list1, data);
    }
    dllSentinelPrint(linked_list1);

    // Search.
    LinkedListNode *found = dllSentinelSearch(linked_list1, 5);
    if (found != NULL)
    {
        printf("%d\n", *(int *)found->data);
    }
    else
    {
        printf("NULL\n");
    }

    // Copy.
    DLLSentinel *linked_list2 = dllSentinelCopy(linked_list1);
    int *new_data = (int *)malloc(sizeof(int));
    *new_data = 99;
    dllSentinelAppend(linked_list2, new_data);
    dllSentinelPrint(linked_list1);
    dllSentinelPrint(linked_list2);

    // Delete.
    DLLSentinel *linked_list3 = dllSentinelInit(NULL);
    int *data5 = (int *)malloc(sizeof(int));
    *data5 = 5;
    int *data6 = (int *)malloc(sizeof(int));
    *data6 = 6;
    int *data7 = (int *)malloc(sizeof(int));
    *data7 = 7;
    dllSentinelPrepend(linked_list3, data7);
    dllSentinelPrepend(linked_list3, data6);
    dllSentinelPrepend(linked_list3, data5);
    dllSentinelPrint(linked_list3);
    LinkedListNode *x = dllSentinelSearch(linked_list3, 6);
    if (x != NULL)
    {
        printf("%d\n", *(int *)x->data);
        dllSentinelDelete(linked_list3, x);
    }
    found = dllSentinelSearch(linked_list3, 6);
    if (found != NULL)
    {
        printf("%d\n", *(int *)found->data);
    }
    else
    {
        printf("NULL\n");
    }
    dllSentinelPrint(linked_list3);

    // Delete sentinel error.
    dllSentinelDelete(linked_list3, linked_list3->sentinel);

    // Object.
    DLLSentinel *linked_list4 = dllSentinelInit(keyObjectGetKey);
    char *states[] = {"AL", "AK", "AZ", "AR", "CA", "CO", "CT", "HI", "NH", "NY"};
    for (int i = 0; i < 10; i++)
    {
        KeyObject *kobj = (KeyObject *)malloc(sizeof(KeyObject));
        kobj->state = states[i];
        kobj->key = i;
        dllSentinelAppend(linked_list4, kobj);
    }
    // Simplified print for KeyObject list
    LinkedListNode *current = linked_list4->sentinel->next;
    printf("[");
    if (current != linked_list4->sentinel)
    {
        while (current->next != linked_list4->sentinel)
        {
            KeyObject *kobj = (KeyObject *)current->data;
            printf("%s(%d), ", kobj->state, kobj->key);
            current = current->next;
        }
        KeyObject *kobj = (KeyObject *)current->data;
        printf("%s(%d)", kobj->state, kobj->key);
    }
    printf("]\n");
    LinkedListNode *node5 = dllSentinelSearch(linked_list4, 5);
    if (node5 != NULL)
    {
        KeyObject *kobj = (KeyObject *)node5->data;
        printf("%s(%d)\n", kobj->state, kobj->key);
    }
    KeyObject *new_kobj = (KeyObject *)malloc(sizeof(KeyObject));
    new_kobj->state = "VT";
    new_kobj->key = 17;
    if (node5 != NULL)
    {
        dllSentinelInsert(linked_list4, new_kobj, node5);
        dllSentinelDelete(linked_list4, node5);
    }
    // Simplified print for KeyObject list after modification
    current = linked_list4->sentinel->next;
    printf("[");
    if (current != linked_list4->sentinel)
    {
        while (current->next != linked_list4->sentinel)
        {
            KeyObject *kobj = (KeyObject *)current->data;
            printf("%s(%d), ", kobj->state, kobj->key);
            current = current->next;
        }
        KeyObject *kobj = (KeyObject *)current->data;
        printf("%s(%d)", kobj->state, kobj->key);
    }
    printf("]\n");

    // Free all lists
    dllSentinelFree(linked_list1);
    dllSentinelFree(linked_list2);
    dllSentinelFree(linked_list3);
    dllSentinelFree(linked_list4);

    return 0;
}