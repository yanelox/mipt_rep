#include <stdio.h>

struct sieve_t 
{
    int n;
    char* s;
};

void fill_sieve (struct sieve_t* sv)
{
    int i = 2;

    while (i * i <=  (*sv).n)
    {
        if (((*sv).s)[i] == 0)
            for (int j = 2 * i; j <= (*sv).n; j += i)
                ((*sv).s)[j] = '1';

        i++;
    }
}

int nth_prime (struct sieve_t* sv, int N)
{
    int i = 1, k = 0;

    while (k != N)
    {
        i++;

        if (((*sv).s)[i] == 0)
            k++;
    }

    return i;
}
