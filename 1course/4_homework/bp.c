#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int compare (const void* a, const void* b)
{
    int *a_1 = (int*) a;
    int *b_1 = (int*) b;

    if (*a_1 > *b_1)
        return 1;

    else if (*a_1 == *b_1)
        return 0;

    else 
        return -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    int sum, n;

    int* things;

    int tmp_sum = 0, count = 0;

    int res = scanf ("%d%d", &sum, &n);

    things = (int*) calloc (n, sizeof (int));

    for (int i = 0; i < n; ++i)
        scanf ("%d", things + i);

    qsort (things, n, sizeof (int), compare);

    for (int i = 0; i < n; ++i)
    {
        tmp_sum += things[i];

        if (tmp_sum > sum)
        {
            count = i;

            break;
        }

        count = i + 1;
    }

    printf ("%d\n", count);

    free (things);
}