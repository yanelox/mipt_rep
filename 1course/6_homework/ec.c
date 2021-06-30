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

typedef double (*func_t)(data coef, double x);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double test_func (data coef, double x)
{
    return x * x * sin (x) - 5 * x + 7;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double func (data coef, double x)
{
    return coef.a * x * x * sin (x) + coef.b * x * cos (x) + coef.c;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double sign (double x)
{
    return signbit(x) ? -1 : 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

value rid (func_t f, double left, double right, data coef, int n, double eps)
{
    value new;

    double mid = (left + right) / 2.0;

    double fl = f (coef, left);
    double fr = f (coef, right);
    double fm = f (coef, mid);

    if (f (coef, left) * f (coef, right) > 0)
    {
        new.root = 0;
        new.steps = 0;

        return new;
    }

    new.steps = n + 1;
    new.root = mid + (mid - left) * sign (fl - fr) * fm / (sqrt (fm * fm - fl * fr));

    if (fabs (f (coef, new.root)) < eps)
        return new;

    if (f (coef, new.root) * f (coef, left) > 0)
        left = new.root;

    else
        right = new.root;

    return rid (f, left, right, coef, new.steps, eps);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

value dh (func_t f, double left, double right, data coef, int n, double eps)
{
    value new;

    if (f (coef, left) * f (coef, right) > 0)
    {
        new.root = 0;
        new.steps = 0;

        return new;
    }

    new.root = (left + right) / 2.0;
    new.steps = n + 1;

    if (fabs (f (coef, new.root)) < eps)
        return new;

    if (f (coef, new.root) * f (coef, left) > 0)
        left = new.root;

    else
        right = new.root;

    return dh (f, left, right, coef, new.steps, eps);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

value fp (func_t f, double left, double right, data coef, int n, double eps)
{
    value new;

    double k = (f (coef, right) - f (coef, left)) / (right - left);
    double b = f(coef, left) - k * left;

    if (f (coef, left) * f (coef, right) > 0)
    {
        new.root = 0;
        new.steps = 0;

        return new;
    }

    new.steps = n + 1;
    new.root = - b / k;

    if (fabs (f (coef, new.root)) < eps)
        return new;

    if (f(coef, new.root) * f (coef, left) > 0)
        left = new.root;

    else
        right = new.root;

    return fp (f, left, right, coef, new.steps, eps);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

value sec (func_t f, double left, double right, data coef, int n, double eps)
{
    value new;

    double k = (f (coef, left) - f (coef, right)) / (left - right);
    double b = f (coef, left) - k * left;

    if (f (coef, left) * f (coef, right) > 0)
    {
        new.root = 0;
        new.steps = 0;

        return new;
    }

    new.root = - b / k;
    new.steps = n + 1;

    if (fabs (f (coef, new.root)) < eps)
        return new;

    if (n % 2 != 0)
        right = new.root;

    else
        left = new.root;

    return sec (f, left, right, coef, new.steps, eps);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    data coef;

    double left, right, eps, n;

    value root_rid, root_dh, root_fp, root_sec;

    scanf ("%lf%lf%lf%lf%lf", &coef.a, &coef.b, &coef.c, &n, &eps);
    // scanf ("%lg%lg%lg", &coef.a, &coef.b, &coef.c);

    root_rid = rid (func, n, -n, coef, 0, eps);
    root_dh  = dh  (func, n, -n, coef, 0, eps);
    // root_fp  = fp  (test_func, left, right, coef, 0);
    // root_sec = sec (test_func, left, right, coef, 0);

    // printf ("Rid:\n");
    // printf ("%lg %lg %d\n", root_rid.root, test_func (coef, root_rid.root), root_rid.steps);

    // printf ("Dh:\n");
    // printf ("%lg %lg %d\n", root_dh.root, test_func (coef, root_dh.root), root_dh.steps);

    // printf ("Fp:\n");
    // printf ("%lg %lg %d\n", root_fp.root, test_func (coef, root_fp.root), root_fp.steps);

    // printf ("Sec:\n");
    // printf ("%lg %lg %d\n", root_sec.root, test_func (coef, root_sec.root), root_sec.steps);

    printf ("%d %d\n", root_dh.steps, root_rid.steps);
}