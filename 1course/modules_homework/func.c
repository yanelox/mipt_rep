#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void read_mas (int* count, double** cord, char* file_name)
{
    FILE* f;

    assert (file_name);

    f = fopen (file_name, "r");

    assert (f);

    fscanf (f, "%d", count);

    *cord = (double*) calloc (6 * *count, sizeof (double));

    for (int i = 0; i < *count; ++i)
        for (int j = 0; j < 6; ++j)
            fscanf (f, "%lf", *cord + 6 * i + j);

    fclose (f);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double tr_area (double* start)
{
    assert (start);

    double res = (start[2] - start[0]) * (start[5] - start[1]) - (start[4] - start[0]) * (start[3] - start[1]);

    res /= 2;

    if (res > 0)
        return res;
    else
        return -res;
}