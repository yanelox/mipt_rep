#include <stdio.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

union fitbits
{
    float f;
    unsigned long long u;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

float magic_first (float x)
{
    union fitbits u;

    u.f = x;
    u.u = (u.u >> 1) + (0x3f800000 >> 1);

    return u.f;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

float my_sqrt (float x)
{
    float res = x / 2;

    for (int i = 0; i < 10; ++i)
        res = (res * res + x) / (2 * res);

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n;

    scanf ("%d", &n);

    for (int i = 1; i < n; ++i)
        printf ("%d : %.6lf - %.6lf\n", i, my_sqrt (i), sqrtf(i));
}