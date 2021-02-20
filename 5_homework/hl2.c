#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct node_t 
{
    struct node_t *next;
    int data;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int loop_len (struct node_t *top)
{
    struct node_t* rabbit = top;
    struct node_t* turtle = top;

    int len = 0;

    if (top == NULL or top->next == NULL)
        return 0;

    while (top and rabbit and turtle)
    {
        if (turtle->next ==  NULL)
            return 0;

        turtle = turtle->next;

        if (rabbit->next == NULL)
            return 0;

        rabbit = rabbit->next;
    
        if (rabbit->next == NULL)
            return 0;

        rabbit = rabbit->next;

        if (rabbit == turtle)
            break; 
    }

    turtle = turtle->next;

    ++len;

    while (rabbit != turtle)
    {
        ++len;
        turtle = turtle->next;
    }

    return len;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    struct node_t* a
}