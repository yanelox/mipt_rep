#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetG    (char* str);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetE    (char** cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetT    (char** cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetS    (char** cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetP    (char** cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetN    (char** cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char** argv)
{
    assert (argc == 2);

    double res = GetG (argv[1]);

    printf ("%lf\n", res);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetG (char* str)
{
    assert (str);

    char* cur_p = str;

    double res = GetE (&cur_p);

    if (*cur_p == '$')
        return res;

    else
        return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetE (char** cur_p)
{
    assert (cur_p);
    assert (*cur_p);

    double res = GetT (cur_p);

    while (**cur_p == '+' or **cur_p == '-')
    {
        int val = 0;

        if (**cur_p == '+')
            val = 1;

        else
            val = -1;

        (*cur_p)++;

        res += val * GetT (cur_p);
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetT (char** cur_p)
{
    assert (cur_p);
    assert (*cur_p);

    double res = GetS (cur_p);

    while (**cur_p == '*' or **cur_p == '/')
    {
        int val = 0;

        if (**cur_p == '*')
            val = 1;
        else
            val = -1;

        (*cur_p)++;

        if (val == 1)
            res *= GetS (cur_p);

        else
            res /= GetS (cur_p);
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetS (char** cur_p)
{
    assert (cur_p);
    assert (*cur_p);

    double res = GetP (cur_p);

    if (**cur_p == '^')
    {
        (*cur_p)++;

        res = pow (res, GetP (cur_p));
    }
    
    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


double GetP (char** cur_p)
{
    assert (cur_p);
    assert (*cur_p);

    double res = 0;

    if (**cur_p == '(')
    {
        (*cur_p)++;

        res = GetE (cur_p);

        if (**cur_p != ')')
            return 0;

        (*cur_p)++;
    }

    else if (isalpha (**cur_p))
    {
        if (**cur_p == 's' and *(*cur_p + 1) == 'i' and *(*cur_p + 2) == 'n' and *(*cur_p + 3) == '(')
        {
            (*cur_p) += 4;

            res = sin (GetE (cur_p));

            if (**cur_p != ')')
                return 0;   

            (*cur_p)++;         
        }

        if (**cur_p == 'c' and *(*cur_p + 1) == 'o' and *(*cur_p + 2) == 's' and *(*cur_p + 3) == '(')
        {
            (*cur_p) += 4;

            res = cos (GetE (cur_p));

            if (**cur_p != ')')
                return 0;   

            (*cur_p)++;         
        }

        if (**cur_p == 'l' and *(*cur_p + 1) == 'n' and *(*cur_p + 2) == '(')
        {
            (*cur_p) += 3;

            res = log (GetE (cur_p));

            if (**cur_p != ')')
                return 0;

            (*cur_p)++;
        }

        if (**cur_p == 't' and *(*cur_p + 1) == 'a' and *(*cur_p + 2) == 'n' and *(*cur_p + 3) == '(')
        {
            (*cur_p) += 4;

            res = tan (GetE (cur_p));

            if (**cur_p != ')')
                return 0;   

            (*cur_p)++;         
        }
    }
    
    else
    {
        res = GetN (cur_p);
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetN (char** cur_p)
{
    assert (cur_p);
    assert (*cur_p);

    double res = 0;
    float n = 10;

    while (**cur_p >= '0' and **cur_p <= '9')
    {
        res = res * 10 + **cur_p - '0';

        (*cur_p)++;
    }

    if (**cur_p == '.')
    {
        (*cur_p)++;

        while (**cur_p >= '0' and **cur_p <= '9')
        {
            res += (**cur_p - '0') / n;

            n *= 10;

            (*cur_p)++;
        }
    }

    return res;
}