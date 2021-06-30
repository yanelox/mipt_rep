#include <stdio.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
    double a;
    double b;
    double c;
} data;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
    double root;
    int steps;

} value;


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct func_deriv 
{ 
    double func; 
    double der; 
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct func_deriv (*fder_t) (data coef, double x);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double eps = 0.00001;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct func_deriv func (data coef, double x)
{
    struct func_deriv res;

    res.func = coef.a * x * x * sin (x) + coef.b * x * cos (x) + coef.c;
    res.der  = coef.a * (2 * x * sin (x) + x * x * cos (x)) + coef.b * (cos (x) - x * sin (x));

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

value newton (fder_t f, double x, data coef, int n)
{
    value new;

    struct func_deriv res = f (coef, x);

    if (n > 100)
    {
        new.root = 0.0;
        new.steps = n + 1;

        return new;
    }

    new.root = x - res.func / res.der;
    new.steps = n + 1;

    res = f (coef, new.root);

    if (fabs (res.func) < eps)
        return new;

    return newton (f, new.root, coef, new.steps);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    data coef;

    value root;

    scanf ("%lf%lf%lf%lf", &coef.a, &coef.b, &coef.c, &root.root);

    root = newton (func, root.root, coef, 0);

    printf ("%.5lf\n", root.root);
}