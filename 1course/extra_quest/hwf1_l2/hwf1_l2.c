#include "head.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int** perm (int n, int* m, int* a, int k, int** res, int* size)
{
    if (k < n)
    {
        for (int i = 0; i < n; ++i)
            if (a[i] != 1)
            {
                m[k] = i + 1;

                a[i] = 1;

                res = perm (n, m, a, k + 1, res, size);

                a[i] = 0;
            }
    }

    else
    {
        int sum = m[0] + m[n/2 - 1] + m[n - 1];

        int cur_sum = 0;

        for (int i = 0; i < n/2 - 1; ++i)
        {
            cur_sum = m[i] + m[i + 1] + m[n/2 + i];

            if (cur_sum != sum)
                return res;
        }

        res = realloc (res, (*size + 1) * sizeof (int*));

        res[*size - 1] = calloc (n, sizeof (int));

        assert (res[*size - 1]);

        for (int i = 0; i < n; ++i)
            res[*size - 1][i] = m[i];

        *size = *size + 1;
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    int n = 0;

    int *mass, *a;

    int size = 1;

    int **res;

    int *tmp1 = calloc (2 * n, sizeof (int)), 
        *tmp2 = calloc (2 * n, sizeof (int)),
        *tmp3 = calloc (n, sizeof (int));

    assert (scanf ("%d", &n) == 1);

    mass = calloc (2 * n, sizeof (int));
    a    = calloc (2 * n, sizeof (int));
    res  = calloc (1,     sizeof (int*));

    res = perm (2 * n, mass, a, 0, res, &size);


    // for (int i = 0; i < size; ++i)
    //     if (res[i])
    //     {
    //         patpreproc (res[i], tmp3, n);

    //         for (int j = i + 1; j < size; ++j)
    //             if (res[j])
    //             {
    //                 for (int k = 0; k < n; ++k)
    //                     tmp1[k] = tmp1[n + k] = tmp2[2 * n - 1 - k] = tmp2[n - 1 - k] = res[j][k];
                    
    //                 if (strstrci (res[i], tmp3, tmp1, n, 2 * n) ||
    //                     strstrci (res[i], tmp3, tmp2, n, 2 * n))
    //                 {
    //                     free (res[j]);
    //                     res[j] = NULL;
    //                 }
    //             }
    //     }


    for (int j = 0; j < size - 1; ++j)
        if (res[j])
        {
            for (int i = 0; i < 2 * n; ++i)
                printf ("%d ", res[j][i]);

            printf ("\n");
        }

    for (int i = 0; i < size - 1; ++i)
        if(res[i])
            free (res[i]);

    free (res);
    free (mass);
    free (a);
    free (tmp1);
    free (tmp2);
    free (tmp3);
}