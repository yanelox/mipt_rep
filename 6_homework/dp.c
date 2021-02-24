#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int con = 10;
float eps = 0.000001;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

float* gen_m (float* a, int n, float det)
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

float* rand_m (float* a, int n)
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

float print_m (float* a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf ("%lg ", a[i * n + j]);

        printf ("\n");
    }

    printf ("\n");

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

float f_det (float* a, int n)
{
    int k_m, j_m;

    float max = a[0];

    float swap = 0;

    float res = 1;

    // printf ("%lg\n", a[n * n - 1]);

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

        // print_m (a, n);
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

    float* a = NULL;

    float det;

    float res_det = 0;

    srand (time (NULL));

    scanf ("%d", &n);

    a = calloc (n * n, sizeof (float));

    for (int i = 0; i < n * n; ++i)
        scanf ("%f", a + i);

    // gen_m (a, n, det);

    // rand_m (a, n);

    // print_m (a, n);

    // res_det = f_det (a, n);

    printf ("%lg\n", res_det);   

    free (a);
}