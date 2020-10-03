#include <stdio.h>
#include <math.h>

int t (unsigned long long n)
{
    unsigned long long i = 0;

    for(i = 2; i < sqrt(n) + 1; i ++)
        if (n % i == 0)
            return 0;
        
    return 1;
}

void pn (unsigned long long n)
{
    unsigned long long x = 1, k = 2;

    while (x < n)
    {
        k++;

        if (t(k))
            x++;
    }

    printf ("%llu", k);
}

int main()
{
    unsigned long long n;

    scanf ("%llu", &n);

    pn (n);
}