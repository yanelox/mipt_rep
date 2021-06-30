#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct node_t {
  struct node_t *next;
  int data;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct node_t * reverse (struct node_t *top)
{
    struct node_t* left = NULL;
    struct node_t* middle = NULL;
    struct node_t* right = NULL;

    if (top == NULL)
        return NULL;

    if (top->next == NULL)
        return top;

    middle = top->next;
    left = top;

    top->next = NULL;

    while (middle->next)
    {
        right = middle->next;
        middle->next = left;

        left = middle;
        middle = right;
    }
    
    return middle;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
