#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int cmp (void* lhs, int lsz, void* rhs, int rcz)
{
    return *((int*) lhs) - *((int*) rhs);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int sum (int* arr, int start, int end)
{
    int res = 0;

    for (int i = start; i <= end; ++i)
        res += arr[i];

    return res;    
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void xmerge (void* mem, int m, int* sizes, int nelts, xcmp_t cmp)
{
    char* el1;
    char* el2;

    int i;
    int j;
    int start = m;

    int sum1 = 0;
    int sum2 = 0;

    sum2 = sum (sizes, 0, m - 1);

    for (i = 0; i < m; ++i)
    {
        el1 = (char*) mem;

        for (j = start; j < nelts; ++j)
        {
            el2 = (char*) mem + sum (sizes, 0, j);

            if (cmp (el1, el2))
                break;
        }

        --j;

        for (int k = 0; )
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp)
{
    int m = nelts / 2;

    int first_sum = 0;

    void* tmp_mem;

    if (m <= 0)
        return;

    for (int i = 0; i < m; ++i)
        first_sum += sizes[i];

    tmp_mem = (void*) ((char*) mem + first_sum);

    xmsort (mem, sizes, m, cmp);
    xmsort (tmp_mem, sizes + m, nelts - m, cmp);
    xmerge (mem, m, sizes, nelts, cmp);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int a[] = {1, 5, 6, 2, 8, 9, 4, 7, 3, 0};
    int size [10];

    for (int i = 0; i < 10; i++)
        size[i] = sizeof(int);

    xmsort ((void*) a, size, 10, &cmp);

    for (int i = 0; i < 10; i++)
        printf ("%d ", a[i]);
}