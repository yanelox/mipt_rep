#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct node_t
{
    struct node_t* next;

    int data;

    int number;
};

typedef struct node_t node;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

node* feel_cl (int* m, int number)
{
    int node_number = m[number - 1];

    int* mass = calloc (node_number, sizeof (int));

    node* cycle = NULL;

    for (int i = 0; i < number; ++i)
        mass[m[i] - 1] = 1;
    
    for (int i = 0; i < node_number; ++i)
    {
        if (mass[i] != 1)
        {
            int min = 0;
            for (int j = 0; j < number; ++j)
                if (i - m[j] >= 0 and mass[i - m[j]] > 0 and (min == 0 or min < mass[i - m[j]] + 1))
                    min = mass [i - m[j]] + 1;

            mass[i] = min;
        }

        // printf ("%d\n", mass[i]);
    }

    cycle = calloc (node_number, sizeof (node));

    for (int i = 0; i < node_number - 1; ++i)
    {
        cycle[i].data   = mass[i];
        cycle[i].number = i + 1;
        cycle[i].next   = cycle + i + 1;
    }

    cycle[node_number - 1].data   = mass[node_number - 1];
    cycle[node_number - 1].number = node_number;
    cycle[node_number - 1].next = cycle;

    free (mass);

    return cycle;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int sum = 0, number = 0, cur = 0;  
    int* m = NULL;

    node* cycle = NULL, *start = NULL;
    node** p = NULL;

    scanf ("%d%d", &sum, &number);

    m = calloc (number, sizeof (int));

    for (int i = 0; i < number; ++i)
        scanf ("%d", m + i);

    start = feel_cl (m, number);
    cycle = start;

    cur = m[number - 1] + 1;

    p = calloc (number, sizeof (node*));

    for (int i = 0; i < number; ++i)
        p[i] = start + m[number - 1] - m[i];

    // for (int i = 0; i < m[number - 1]; ++i)
    //     printf ("%d %d\n", start[i].number, start[i].data);

    while (cur <= sum)
    {
        int min = 0;

        for (int i = 0; i < number; ++i)
        {
            if (p[i]->data > 0 and (min == 0 or min > p[i]->data + 1))
                min = p[i]->data + 1;

            p[i] = p[i]->next;
        }

        cycle->data   = min;
        cycle->number = cur;
        
        if (cur < sum)
            cycle = cycle->next;

        ++cur;

        // printf ("%d %d\n", cycle->number, cycle->data);
    }

    printf ("%d\n", cycle->data);

    free (p);
    free (start);
    free (m);
}