#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct node_t 
{
    struct node_t *next;

    int data;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct node_t *read_list (FILE *inp)
{
    int number = 0;

    struct node_t* start_even = NULL;
    struct node_t* prev_even  = NULL;

    struct node_t* start_odd  = NULL;
    struct node_t* prev_odd   = NULL;

    struct node_t* cur        = NULL;

    while (fscanf (inp, "%d", &number) == 1)
    {
        cur = calloc (1, sizeof (struct node_t));
        cur->data = number;

        if (number % 2 == 0)
        {
            if (!start_even)
                start_even = cur;

            if (prev_even)
                prev_even->next = cur;

            prev_even = cur;
        }

        else
        {
            if (!start_odd)
                start_odd = cur;

            if (prev_odd)
                prev_odd->next = cur;

            prev_odd = cur;
        }
    }

    if (!start_even)
        return start_odd;

    if (!start_odd)
        return start_even;

    prev_even->next = start_odd;

    return start_even;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void delete_list (struct node_t *top)
{
    struct node_t* next;

    while (top)
    {
        next = top->next;

        free (top);

        top = next;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    FILE* file = fopen ("smth.txt", "r");

    struct node_t* ayf = read_list (file);

    fclose (file);

    delete_list (ayf);
}