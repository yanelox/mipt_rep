#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

float eps = 0.01;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double f_det (double* a, int n)
{
    int k_m, j_m;

    float max = a[0];

    float swap = 0;

    float res = 1;

    for (int i = 0; i < n - 1; ++i)
    {
        max = a[i * n + i];

        for (int j = i; j < n; ++j)
        for (int k = i; k < n; ++k)
            if (a[j * n + k] > max)
            {
                max = a[j * n + k];
                j_m = j;
                k_m = k;
            }

        for (int j = 0; j < n; ++j)
        {
            swap = a[i * n + j];
            a[i * n + j] = a[j_m * n + j];
            a[j_m * n + j] = swap;
        }

        for (int j = 0; j < n; ++j)
        {
            swap = a[j * n + i];
            a[j * n + i] = a[j * n + k_m];
            a[j * n + k_m] = swap;
        }

        if (abs (a[i * n + i]) < eps)
        {
            printf ("\n1-%lg\n", fabs (a[n * n - 1]));
            return 6.66;
        }

        for (int j = i + 1; j < n; ++j)
        {
            float coef = a[j * n + i] / a[i * n + i];

            for (int k = 0; k < n; ++k)
                a[j * n + k] -= coef * a[i * n + k];
        }

    }

    if (fabs (a[n * n - 1]) < eps)
    {
        printf ("\n2-%lg\n", fabs (a[n * n - 1]));
        return 6.66;
    }

    for (int i = 0; i < n; ++i)
        res *= a[i * n + i];

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n;

    double* a = NULL;

    double res_det;

    scanf ("%d", &n);

    a = calloc (n * n, sizeof (double));

    for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
        scanf ("%lg", a + j * n + i);

    res_det = f_det (a, n);

    printf ("%lg\n", res_det);

    free (a);
}