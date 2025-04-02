#include <stdio.h>
#include <stdlib.h>

// Define the queue structure
typedef struct
{
    int *array;
    int size;
    int head;
    int tail;
} Queue;

// Initialize a queue of n elements.
Queue *createQueue(int n)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    q->array = (int *)calloc(n + 1, sizeof(int));
    if (q->array == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(q);
        exit(EXIT_FAILURE);
    }
    q->size = n;
    q->head = 0;
    q->tail = 0;
    return q;
}

// Return a boolean indicating whether the queue is empty.
int isEmpty(Queue *q)
{
    return q->head == q->tail;
}

// Add an element to the tail of the queue.
void enqueue(Queue *q, int x)
{
    // Check for queue overflow. Must always have at least 1 empty slot.
    if (q->head == (q->tail + 1) % q->size)
    {
        fprintf(stderr, "Queue is full.\n");
        exit(EXIT_FAILURE);
    }
    q->array[q->tail] = x;
    // Wrap around index of tail if the end of the array is reached.
    q->tail = (q->tail + 1) % q->size;
}

// Remove an element from the head of the queue.
int dequeue(Queue *q)
{
    if (isEmpty(q))
    { // queue underflow?
        fprintf(stderr, "Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        int x = q->array[q->head];
        // Wrap around the index of the head if the end of the array is reached.
        q->head = (q->head + 1) % q->size;
        return x;
    }
}

// Return the string representation of the queue, from head to tail.
void printQueue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("[]\n");
        return;
    }
    printf("[");
    if (q->head <= (q->tail - 1) % q->size)
    {
        for (int i = q->head; i < ((q->tail - 1) % q->size) + 1; i++)
        {
            printf("%d", q->array[i]);
            if (i < ((q->tail - 1) % q->size))
            {
                printf(", ");
            }
        }
    }
    else
    {
        for (int i = q->head; i < q->size + 1; i++)
        {
            printf("%d", q->array[i]);
            if (i < q->size || q->tail > 0)
            {
                printf(", ");
            }
        }
        for (int i = 0; i < q->tail; i++)
        {
            printf("%d", q->array[i]);
            if (i < q->tail - 1)
            {
                printf(", ");
            }
        }
    }
    printf("]\n");
}

// Free the queue memory
void freeQueue(Queue *q)
{
    free(q->array);
    free(q);
}

int main()
{
    // Testing
    // Textbook example.
    Queue *queue1 = createQueue(11);
    // Put in 6 values.
    for (int i = 100; i < 106; i++)
    {
        enqueue(queue1, i);
    }
    printQueue(queue1); // should print True
    for (int i = 0; i < 6; i++)
    {
        printf("%d\n", dequeue(queue1));
    }
    printf("%d\n", isEmpty(queue1));
    enqueue(queue1, 15);
    enqueue(queue1, 6);
    enqueue(queue1, 9);
    enqueue(queue1, 8);
    enqueue(queue1, 4);
    printQueue(queue1);
    enqueue(queue1, 17);
    printQueue(queue1);
    enqueue(queue1, 3);
    printQueue(queue1);
    enqueue(queue1, 5);
    printQueue(queue1);
    printf("%d\n", dequeue(queue1));
    printQueue(queue1);

    // Empty queue1 and then try to dequeue.
    while (!isEmpty(queue1))
    {
        dequeue(queue1);
    }
    if (isEmpty(queue1))
    {
        fprintf(stderr, "Queue is empty.\n");
    }

    // Queue overflow.
    Queue *queue2 = createQueue(10);
    for (int i = 0; i < 9; i++)
    {
        enqueue(queue2, i);
    }
    printQueue(queue2);
    if ((queue2->tail + 1) % queue2->size == queue2->head)
    {
        fprintf(stderr, "Queue is full.\n");
    }

    freeQueue(queue1);
    freeQueue(queue2);
    return 0;
}