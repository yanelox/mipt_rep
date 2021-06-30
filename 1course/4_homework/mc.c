#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int f (int sum, int* a, int n)
{
    int min = sum + 1;

    int fin_res = 0;

    int* res = (int*) calloc (sum + 1, sizeof (int));

    for (int i = 1; i <= sum; ++i)
    {
        min = sum + 1;

        for (int j = 0; j < n; ++j)
            if ((i - a[j] >= 0) and (min > res[i - a[j]] + 1))
                min = res[i - a[j]] + 1;
        

        res[i] = min;
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