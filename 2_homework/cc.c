#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int IsSimple (int a)
{
    for (int i = 2; i * i <= a; ++i)
        if (a % i == 0)
            return 0;

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int cc (int a)
{
    int k = 1;
    int r = 0;
    int b = a;
    int s = 0;

    while (b)
    {
        b /= 10;
        ++r;
        k *= 10;
    }

    k /= 10;

    for (int i = 0; i < r; ++i)
    {
        if (IsSimple (a))
            ++s;

        b = a % 10;
        a /= 10;
        a += b * k;
    }

    if (s == r)
        return 1;

    else
        return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n;
    int a;
    int b;

    scanf ("%d", &n);

    a = n;
    b = n;

    while ((cc (a) == 0) and (cc (b) == 0))
    {
        if (a > 1)
            a--;
        
        b++;
    }

    if (cc (a) == 1)
        if (cc (b) != 1 or (cc (b) == 1) and (n - a < b - n))
            printf ("%d", a);

        else    
            printf ("%d", b);

    else
        printf ("%d", b);
}