#include <stdio.h>
#include <stdlib.h>

// Forward declaration of LinkedList for function pointer
typedef struct LinkedList LinkedList;

// Define the node structure
typedef struct LinkedListNode
{
    struct LinkedListNode *prev;
    struct LinkedListNode *next;
    void *data;
} LinkedListNode;

// Function pointer type for get_key function
typedef int (*GetKeyFunc)(void *);

// Define the linked list structure
typedef struct LinkedList
{
    LinkedListNode *head;
    GetKeyFunc get_key;
} LinkedList;

// Identity function for get_key
int identityGetKey(void *data)
{
    return *(int *)data;
}

// Initialize a node of a doubly linked list with the given data.
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

// Initialize an empty doubly linked list with only a head pointer.
//
// Argument:
// get_key_func -- an optional function that returns the key for the
// objects stored. May be a static function in the object class. If
// omitted, then identity function is used.
LinkedList *linkedListInit(GetKeyFunc get_key_func)
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    if (get_key_func == NULL)
    {
        list->get_key = identityGetKey;
    }
    else
    {
        list->get_key = get_key_func;
    }
    return list;
}

// Search a doubly linked list for a node with key k.
//
// Returns:
// x -- a node with key k or NULL if not found
LinkedListNode *linkedListSearch(LinkedList *list, int k)
{
    LinkedListNode *x = list->head;
    // get_key_func used in searching.
    while (x != NULL && list->get_key(x->data) != k)
    {
        x = x->next;
    }
    return x;
}

// Insert a node with data after node y.  Return the new node.
LinkedListNode *linkedListInsert(LinkedList *list, void *data, LinkedListNode *y)
{
    LinkedListNode *x = linkedListNodeInit(data);
    x->next = y->next;
    x->prev = y;
    if (y->next != NULL)
    {
        y->next->prev = x;
    }
    y->next = x;
    return x;
}

// Insert a node with data as the head of a doubly linked list.  Return the new node.
LinkedListNode *linkedListPrepend(LinkedList *list, void *data)
{
    LinkedListNode *x = linkedListNodeInit(data);
    x->next = list->head;
    if (list->head != NULL)
    {
        list->head->prev = x;
    }
    list->head = x;
    x->prev = NULL;
    return x;
}

// Remove a node x from a doubly linked list.
//
// Assumption:
// x is a node in the linked list.
void linkedListDelete(LinkedList *list, LinkedListNode *x)
{
    if (x->prev != NULL)
    {
        x->prev->next = x->next;
    }
    else
    {
        list->head = x->next;
    }
    if (x->next != NULL)
    {
        x->next->prev = x->prev;
    }
    free(x);
}

// Delete all nodes in a doubly linked list.
void linkedListDeleteAll(LinkedList *list)
{
    LinkedListNode *current = list->head;
    while (current != NULL)
    {
        LinkedListNode *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

// Print the linked list in a similar format as Python's __str__
void linkedListPrint(LinkedList *list)
{
    printf("[");
    LinkedListNode *x = list->head;
    if (x != NULL)
    {
        while (x->next != NULL)
        {
            printf("%d, ", *(int *)x->data);
            x = x->next;
        }
        printf("%d", *(int *)x->data);
    }
    printf("]\n");
}

// Return a copy of this doubly linked list.
LinkedList *linkedListCopy(LinkedList *list)
{
    LinkedList *c = linkedListInit(list->get_key);
    LinkedListNode *x = list->head;
    LinkedListNode *last = NULL;
    if (x != NULL)
    {
        last = linkedListPrepend(c, x->data);
        x = x->next;
    }
    while (x != NULL)
    {
        last = linkedListInsert(c, x->data, last);
        x = x->next;
    }
    return c;
}

// Free the linked list memory
void linkedListFree(LinkedList *list)
{
    linkedListDeleteAll(list);
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
    LinkedList *linked_list1 = linkedListInit(NULL);
    for (int i = 0; i < 10; i++)
    {
        int *data = (int *)malloc(sizeof(int));
        *data = i;
        linkedListPrepend(linked_list1, data);
    }
    linkedListPrint(linked_list1);

    // Search.
    LinkedListNode *found = linkedListSearch(linked_list1, 5);
    if (found != NULL)
    {
        printf("%d\n", *(int *)found->data);
    }
    else
    {
        printf("NULL\n");
    }

    // Copy.
    LinkedList *linked_list2 = linkedListCopy(linked_list1);
    int *new_data = (int *)malloc(sizeof(int));
    *new_data = 99;
    linkedListPrepend(linked_list2, new_data);
    linkedListPrint(linked_list1);
    linkedListPrint(linked_list2);

    // Delete.
    LinkedList *linked_list3 = linkedListInit(NULL);
    int *data5 = (int *)malloc(sizeof(int));
    *data5 = 5;
    int *data6 = (int *)malloc(sizeof(int));
    *data6 = 6;
    int *data7 = (int *)malloc(sizeof(int));
    *data7 = 7;
    linkedListPrepend(linked_list3, data7);
    linkedListPrepend(linked_list3, data6);
    linkedListPrepend(linked_list3, data5);
    linkedListPrint(linked_list3);
    LinkedListNode *x = linkedListSearch(linked_list3, 6);
    if (x != NULL)
    {
        printf("%d\n", *(int *)x->data);
        linkedListDelete(linked_list3, x);
    }
    found = linkedListSearch(linked_list3, 6);
    if (found != NULL)
    {
        printf("%d\n", *(int *)found->data);
    }
    else
    {
        printf("NULL\n");
    }
    linkedListPrint(linked_list3);

    // Object.
    LinkedList *linked_list4 = linkedListInit(keyObjectGetKey);
    char *states[] = {"AL", "AK", "AZ", "AR", "CA", "CO", "CT", "HI", "NH", "NY"};
    for (int i = 0; i < 10; i++)
    {
        KeyObject *kobj = (KeyObject *)malloc(sizeof(KeyObject));
        kobj->state = states[i];
        kobj->key = i;
        linkedListPrepend(linked_list4, kobj);
    }
    // Simplified print for KeyObject list
    LinkedListNode *current = linked_list4->head;
    printf("[");
    if (current != NULL)
    {
        while (current->next != NULL)
        {
            KeyObject *kobj = (KeyObject *)current->data;
            printf("%s(%d), ", kobj->state, kobj->key);
            current = current->next;
        }
        KeyObject *kobj = (KeyObject *)current->data;
        printf("%s(%d)", kobj->state, kobj->key);
    }
    printf("]\n");
    LinkedListNode *node5 = linkedListSearch(linked_list4, 5);
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
        linkedListInsert(linked_list4, new_kobj, node5);
        linkedListDelete(linked_list4, node5);
    }
    // Simplified print for KeyObject list after modification
    current = linked_list4->head;
    printf("[");
    if (current != NULL)
    {
        while (current->next != NULL)
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
    linkedListFree(linked_list1);
    linkedListFree(linked_list2);
    linkedListFree(linked_list3);
    linkedListFree(linked_list4);

    return 0;
}