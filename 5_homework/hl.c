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

int list_is_a_loop (struct node_t *top)
{
    struct node_t* rabbit = top;
    struct node_t* turtle = top;

    

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
            return 1; 
    }

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    struct node_t* a
}