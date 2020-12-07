#include <stdio.h>
#include <assert.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetG    (char* str);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetE    (char** cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetT    (char** cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetS    (char** cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetP    (char** cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetN    (char** cur_p);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main (int argc, char** argv)
{
    assert (argc == 2);

    int res = GetG (argv[1]);

    printf ("%d\n", res);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetG (char* str)
{
    assert (str);

    char* cur_p = str;

    int res = GetE (&cur_p);

    if (*cur_p == '$')
        return res;

    else
        return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetE (char** cur_p)
{
    assert (cur_p);
    assert (*cur_p);

    int res = GetT (cur_p);

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

int GetT (char** cur_p)
{
    assert (cur_p);
    assert (*cur_p);

    int res = GetS (cur_p);

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

int GetS (char** cur_p)
{
    assert (cur_p);
    assert (*cur_p);

    int res = GetP (cur_p);

    if (**cur_p == '^')
    {
        (*cur_p)++;

        res = pow (res, GetP (cur_p));
    }
    
    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


int GetP (char** cur_p)
{
    assert (cur_p);
    assert (*cur_p);

    int res = 0;

    if (**cur_p == '(')
    {
        (*cur_p)++;

        res = GetE (cur_p);

        if (**cur_p != ')')
        {
            return 0;
        }

        (*cur_p)++;
    }
    
    else
    {
        res = GetN (cur_p);
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int GetN (char** cur_p)
{
    assert (cur_p);
    assert (*cur_p);

    int res = 0;

    while (**cur_p >= '0' and **cur_p <= '9')
    {
        res = res * 10 + **cur_p - '0';

        (*cur_p)++;
    }

    return res;
}