#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int con = 10;
double eps = 0.0001;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double* gen_m (double* a, int n, double det)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i == j)
                a[i * n + j] = 1;

            else if (j > i)
                a[i * n + j] = rand () % con;

    a[n * n - 1] = det;

    return a;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double* rand_m (double* a, int n)
{
    int k = 0;

    for (int i = 1; i < n; ++i)
    {
        k = rand() % con;

        for (int j = 0; j < n; ++j)
            a[i * n + j] += k * a[j];
    }

    k = rand () % con;

    for (int i = 0; i < n; ++i)
        a[i] += k * a[(n - 1) * n + i];

    return a;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double print_m (double* a, int n)
{
    printf ("\n");

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf ("\t%.3lg", a[i * n + j]);

        printf ("\n");
    }

    printf ("\n");

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double f_det (double* a, int n)
{
    int k_m, j_m;

    int mul = 1;

    double max = fabs (a[0]);

    double swap = 0;

    double res = 1;

    for (int i = 0; i < n - 1; ++i)
    {
        max = fabs (a[i * n + i]);
        k_m = i;
        j_m = i;

        for (int j = i; j < n; ++j)
            for (int k = i; k < n; ++k)
                if (fabs (a[j * n + k]) > max)
                {
                    max = fabs (a[j * n + k]);
                    j_m = j;
                    k_m = k;
                }

        if (j_m != i)
        {    
            for (int j = 0; j < n; ++j)
            {
                swap = a[i * n + j];
                a[i * n + j] = a[j_m * n + j];
                a[j_m * n + j] = swap;
            }

            mul *= -1;
        }

        if (k_m != i)
        {
            for (int j = 0; j < n; ++j)
            {
                swap = a[j * n + i];
                a[j * n + i] = a[j * n + k_m];
                a[j * n + k_m] = swap;
            }

            mul *= -1;
        }

        // printf ("//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n%d\n", i);
        // print_m (a, n);

        if (fabs (a[i * n + i]) < eps)
        {
            // printf ("%lg\n", a[i * n + i]);
            return 0;
        }

        for (int j = i + 1; j < n; ++j)
        {
            double coef = a[j * n + i] / a[i * n + i];

            for (int k = 0; k < n; ++k)
                a[j * n + k] -= coef * a[i * n + k];
        }

        // print_m (a, n);
        // printf ("//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    }

    if (fabs (a[n * n - 1]) < eps)
    {
        // printf ("%lg\n", a[n * n - 1]);
        return 0;
    }

    for (int i = 0; i < n; ++i)
        res *= a[i * n + i];

    return mul * res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n;

    double* a = NULL;

    double res_det = 0;

    scanf ("%d", &n);

    a = calloc (n * n, sizeof (double));

    for (int i = 0; i < n * n; ++i)
        scanf ("%lg", a + i);

    // print_m (a, n);

    // res_det = f_det (a, n);

    // printf ("%lg\n", res_det);  

    free (a);
}