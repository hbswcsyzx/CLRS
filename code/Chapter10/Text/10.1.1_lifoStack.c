#include <stdio.h>
#include <stdlib.h>

// Define the stack structure
typedef struct
{
    int *stack;
    int size;
    int top;
} Stack;

// Initialize a stack with an array of length n.
Stack *createStack(int n)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    s->stack = (int *)calloc(n, sizeof(int));
    if (s->stack == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(s);
        exit(EXIT_FAILURE);
    }
    s->size = n;
    s->top = -1;
    return s;
}

// Return a boolean indicating whether the stack is empty.
int isEmpty(Stack *s)
{
    return s->top == -1;
}

// Add an element to the top of the stack.
void push(Stack *s, int x)
{
    if (s->top == s->size - 1)
    {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        s->top += 1;
        s->stack[s->top] = x;
    }
}

// Remove the top element from the stack and return it.
int pop(Stack *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        int val = s->stack[s->top];
        s->top -= 1;
        return val;
    }
}

// Print the stack up to top element.
void printStack(Stack *s)
{
    printf("[");
    for (int i = 0; i <= s->top; i++)
    {
        printf("%d", s->stack[i]);
        if (i < s->top)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

// Free the stack memory
void freeStack(Stack *s)
{
    free(s->stack);
    free(s);
}

int main()
{
    // Testing
    Stack *stack1 = createStack(5);
    printStack(stack1);
    push(stack1, 1);
    printStack(stack1); // one element: 1
    push(stack1, 2);
    push(stack1, 100);
    printStack(stack1);          // three elements: 1, 2, 100
    printf("%d\n", pop(stack1)); // pop 100 out
    printStack(stack1);
    printf("%d\n", pop(stack1));     // pop 2 out
    printf("%d\n", pop(stack1));     // pop 1 out
    printf("%d\n", isEmpty(stack1)); // should be true
    if (isEmpty(stack1))
    {
        fprintf(stderr, "Stack underflow.\n");
    }

    // Check for overflow.
    Stack *stack2 = createStack(10);
    for (int i = 0; i < 11; i++)
    {
        if (i == 10)
        {
            fprintf(stderr, "Stack overflow\n");
        }
        else
        {
            push(stack2, i);
        }
    }
    printStack(stack2);

    freeStack(stack1);
    freeStack(stack2);
    return 0;
}