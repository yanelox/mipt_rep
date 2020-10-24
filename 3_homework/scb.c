#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef int (*cmp_t)(const void *lhs, const void *rhs);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void *cbsearch(const void *key, const void *base, int num, int size, cmp_t cmp)
{
    int l = 0;
    int r = num - 1;

    while (l <= r)
    {
        int m = l + (r - l) / 2;

        const void* tmp = (const void*)((char*) base + m * size);

        int res = cmp (key, tmp);

        if (res == 0) 
            return tmp;

        if (res < 0)
            r = m -1;
        
        if (res > 0)
            l = m + 1;
    }

    return NULL;
}   

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
