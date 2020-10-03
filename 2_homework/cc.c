#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct sieve_t
{
    unsigned n;
    char *s;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned get_bit (char x, unsigned k)
{
    return (x >> k) & 1u; 
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void set_bit (char* x, unsigned k)
{
    *x = *x | (1u << k);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void fill_sieve (struct sieve_t* sv)
{
    int i = 2, x, j;

    *((*sv).s) = 1;
    *((*sv).s + 1) = 1;
    
    for (i = 2; i * i <= 8 * (*sv).n; i++)
    {
	x = get_bit (*((*sv).s + i / 8), i % 8);

        if (!x)
            for (j = i * i; j <= 8 * (*sv).n; j += i)
                set_bit ((*sv).s + j / 8, j % 8);
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int is_prime (struct sieve_t* sv, unsigned n)
{
    int x = get_bit (*((*sv).s + n / 8), n % 8);
    return x;
}

int main ()
{
    ;
}