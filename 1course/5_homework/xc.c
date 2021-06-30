#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef int (*get_hash_t)(const char *s);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int compare (const void* a, const void* b)
{
    int ma = *((int*) a);
    int mb = *((int*) b);

    if (ma > mb)
        return 1;

    else if (ma == mb)
        return 0;

    else 
        return -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int ncollisions (char **strs, int n, get_hash_t f)
{
    int* a = calloc (n, sizeof (int));
    int res = 0;

    for (int i = 0; i < n; ++i)
        a[i] = f (strs[i]);

    qsort (a, n, sizeof (int), compare);

    for (int i = 1; i < n; ++i)
        if (a[i] == a[i - 1])
            ++res;

    free (a);

    return res;
}