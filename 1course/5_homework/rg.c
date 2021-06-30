#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned cycle_len (generator_t gen)
{
    int* mass = calloc (1, sizeof (int));

    int k = 1;

    int n = 1;

    unsigned p = 0;

    while (k)
    {
        ++n;

        realloc (mass, n * sizeof (int));

        mass[n - 1] = gen (mass[n - 2]);

        for (int i = 0; i < n - 1; ++i)
            if (mass[i] == mass[n - 1])
            {
                k = 0;

                p = n - 1 - i;

                break;
            }
    }

    free (mass);

    return p;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
