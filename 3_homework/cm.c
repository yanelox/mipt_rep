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

void xmerge (void* mem, int m, int* sizes, int nelts, xcmp_t cmp)
{
    void* el1;
    void* el2;

    int sum1 = 0;
    int sum2 = 0;

    for (int i = 0; i < m; i++)
        sum2 += sizes[i];

    for (int i = 0, j = m; i < m and j < nelts;)
    {
        el1 = (void*) ((char*) mem + sum1);
        el2 = (void*) ((char*) mem + sum2);

        sum1 += sizes[i];
        sum2 += sizes[j];

        if (cmp (el1, sizes[i], el2, sizes[j]) > 0)
        {
            char* tmp = (char*) calloc (sizes[j], 1);

            for (int k = 0; k < sizes[j]; k++)
                tmp[j] = *((char*) el2 + j);

            for (int k = sum2 - 1; k >= sum1; k--)
                *((char*) el2 + k + sizes[j]) = *((char*) el2 + k);

            for (int k = 0; k < sizes[j]; k++)
                *((char*) el1 + k) = tmp[k];

            j++;

            free (tmp);
        }

        i++;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp)
{
    int m = nelts / 2;

    int first_sum = 0;

    void* tmp_mem;

    if (nelts <= 0)
        return;

    for (int i = 0; i < m; i++)
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