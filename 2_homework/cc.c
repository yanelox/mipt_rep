#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define or ||
#define and &&

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int is_prime (unsigned n)
{
    for (int i = 2; i < sqrt(n) + 1; i++)
        if (n % i == 0)
            return 0;

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int can_be_cs (unsigned n)
{
    while (n > 0)
    {
        if (n % 10 != 1 and n % 10 != 3 and n % 10 != 7 and n % 10 != 9)
            return 0;

        n /= 10;
    }

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int is_cs (unsigned n)
{
    int k = 1, c = n, g = n;

    while (c > 0)
    {
        k *= 10;
        c /= 10;
    }

    k /= 10;

    do
    {
        if (!is_prime(g))
            return 0;

        g = (n % 10) * k + n / 10;
    }

    while (g != n);
    
    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned near_cs (unsigned n)
{
    int i = 1;

    for (;;)
    {
        if (n - i > 0 and is_cs (n - i))
            return n - i;

        if (is_cs(n + i))
            return n + i;

        i++;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n;
    
    scanf ("%d", &n);

    printf ("%d", near_cs (n));
}