#include <stdio.h>
#include <math.h>
#include <fenv.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

float ulp (float a)
{

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int a, b;

    float res;

    fesetround (FE_DOWNWARD);

    scanf ("%d%d", &a, &b);

    res = (float) a / (float) b;
}