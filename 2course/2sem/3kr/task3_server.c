#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void random_matrix (int* m, int n1, int n2)
{
    int i, j;
    for (i = 0; i < n1; i++)
        for (j = 0; j < n2; j++)
            m[i * n2 + j] = rand () % 100;
}

void print_matrix (int* m, int n1, int n2)
{
    int i, j;

    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
            printf ("%d ", m[i * n2 + j]);

        printf ("\n");
    }
}

int main (int argc, char* argv[])
{
    int m_size = 1000;

    int rank, size;

    int m = m_size, n = m_size, p = m_size;

    int* m1 = calloc (m * n, sizeof (int));

    int* m2 = calloc (n * p, sizeof (int));

    random_matrix (m1, m, n);
    random_matrix (m2, n, p);

    MPI_Init (&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int line = m / size;

    int* ans = calloc (sizeof (int), line * p);

    int i, j, k;

    if (rank == 0)
    {
        int* m3 = calloc (m * p, sizeof (int));

        for (i = 1; i < size; i++)
        {
            MPI_Recv (ans, p * line, MPI_INT, i, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (j = 0; j < line; j++)
                for (k = 0; k < p; k++)
                    m3[(j + (i - 1) * line) * p + k] = ans[j * p + k];
        }

        for (i = (size - 1) * line; i < m; i++)
            for (j = 0; j < p; j++)
                for (k = 0; k < n; k++)
                    m3[i * p + j] += m1[i * n + k] * m2 [k * p + j];

        free (m3);
    }

    else
    {
        for (i = 0; i < line; i++)
            for (j = 0; j < p; j++)
                for (k = 0; k < n; k++)
                    ans[i * p + j] += m1[( i + (rank - 1) * line ) * n + k] * m2[k * p + j];

        MPI_Send (ans, line * p, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }

    free (m1);
    free (m2);
    free (ans);

    MPI_Finalize();
}
