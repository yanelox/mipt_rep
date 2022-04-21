#include <stdio.h>
#include <stdlib.h>

void random_matrix (int* m, int n1, int n2)
{
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
            m[i * n2 + j] = rand () % 100;
}

void print_matrix (int* m, int n1, int n2)
{
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
            printf ("%d ", m[i * n2 + j]);

        printf ("\n");
    }
}

int main (int argc, char* argv[])
{
    int m = 1000, n = 1000, p = 1000;

    // scanf ("%d%d%d", &m, &n, &p);

    int* m1 = calloc (m * n, sizeof (int));

    int* m2 = calloc (n * p, sizeof (int));

    int* m3 = calloc (m * p, sizeof (int));

    random_matrix (m1, m, n);
    random_matrix (m2, n, p);

    print_matrix (m1, m, n);
    print_matrix (m2, n, p);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < p; j++)
            for (int k = 0; k < n; k++)
                m3[i * p + j] += m1[i * n + k] * m2[k * p + j];

    print_matrix (m3, m, p);

    free (m1);
    free (m2);
    free (m3);
}