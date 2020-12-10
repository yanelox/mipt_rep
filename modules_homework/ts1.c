#include <stdio.h>
#include <stdlib.h>
#include "func.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    char* file_name = "source.txt";

    int count;
    double* cord;

    double max = 0;
    double res = 0;

    read_mas (&count, &cord, file_name);

    for (int i = 0; i < 6 * count; ++i)
    {
        res = tr_area (cord + i * 6);

        if (res > max)
            max = res;
    }

    printf ("%lf\n", max);

    free (cord);
}