#include <stdio.h>
#include <stdlib.h>
#include "func.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    char* file_name = "source.txt";

    int count;
    double* cord;

    double res = 0;

    read_mas (&count, &cord, file_name);

    for (int i = 0; i < count; ++i)
        res += tr_area (cord + i * 6);

    printf ("%lf\n", res);

    free (cord);
}