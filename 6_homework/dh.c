#include <stdio.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

float eps = 0.0001;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

float func (float a, float b, float c, float x)
{
    return a * x * x * sin (x) + b * x * cos (x) + c; 
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    float a, b, c;

    float n;

    float l, r;
    
    float sol;

    scanf ("%f%f%f%f", &a, &b, &c, &n);

    l = -n;
    r = n;
    sol = (l + r) / 2;

    if (func(a, b, c, l) > 0 && func (a, b, c, r) > 0 || func (a, b, c, l) < 0 && func (a, b, c, r) < 0)
        sol = 0.0;

    else
        while (fabs(func (a, b, c, sol)) >= eps)
        {
            if (func (a, b, c, l) * func (a, b, c, sol) > 0)
                l = sol;

            else
                r = sol;

            sol = (l + r) / 2;
        }

    printf ("%.5f\n", sol);
}