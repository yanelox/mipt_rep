#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define or ||
#define and &&

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned long long mult_m (unsigned long long a, unsigned long long k, unsigned long long m)
{
    unsigned long long res = a % m;
    unsigned long long prod = 0;
    
    while (k > 0)
    {
        if (k % 2 == 1)
        {
            prod = (prod + res) % m;
            k -= 1;
        }
        
        else
        {
            res = (res + res) % m; 
            k /= 2;
        }
    }

    return prod;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned long long pow_m (unsigned long long a, unsigned long long k, unsigned long long m)
{
    unsigned long long res = a % m;
    unsigned long long prod = 1;

    while (k > 0)
    {
        if (k % 2 == 1)
        {
            prod = mult_m (prod, res, m);
            k -= 1;
        }

        else
        {
            res = mult_m (res, res, m);
            k /= 2;
        }
    }

    return prod;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int prime_f (unsigned long long P)
{
    srand (time (NULL));

    for (int i = 0; i < 1000; i++)
    {
        unsigned long long a = (unsigned long long) rand () % P;
        unsigned long long z = (unsigned long long) pow_m (a, P - 1, P);

        if (z % P != 1)
            return 0;
    }

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int simple_test (unsigned long long P)
{
    if (P == 1 or P == 0)
        return 0;

    for (unsigned long long i = 2; i * i <= P; ++i)
        if (P % i == 0)
            return 0;

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    unsigned long long s1 = 0;
    unsigned long long s2 = 1;
    unsigned long long res = 0;
    unsigned long long tmp = 0;
    int k = 0; 
    int n = 0;

    scanf ("%d %d", &k, &n);

    while (s2 < (1llu << 60))
    {
        if (s2 <= (1 << 10) and simple_test (s2) == 1)
            res = s2;

        else if (s2 > (1 << 10) and prime_f (s2) == 1)
            res = s2;

        tmp = s2;
        s2 = k * s2 + n * s1;
        s1 = tmp;
    }

    printf ("%llu", res);
} 