#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int f (int sum, int* a, int n)
{
    int max = 0;

    int k = 0;

    int fin_res = 0;

    int* res = (int*) calloc (sum + 1, sizeof (int));

    for (int i = 1; i <= sum; ++i)
    {
        max = 0;

        for (int j = 0; j < n; ++j)
            if ((a[j] != -1) and (i - a[j] >= 0) and (max < res[i - a[j]] + 1))
            {
                max = res[i - a[j]] + 1;
                k = j;
            }

        a[k] = -1;

        res[i] = max;
    }

    fin_res = res[sum];

    free (res);

    return fin_res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int sum, n;

    int* a = NULL;

    scanf ("%d%d", &sum, &n);

    a = (int*) calloc (n, sizeof (int));

    for (int i = 0; i < n; ++i)
        scanf ("%d", a + i);

    printf ("%d\n", f (sum, a, n));

    free (a);
}