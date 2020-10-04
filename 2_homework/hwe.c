#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct sieve_t {
  int n;
  unsigned char *mod1;
  unsigned char *mod5;  
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void set_bit (unsigned char* a, int k)
{
    *a = *a | (1u << k);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int get_bit (unsigned char *a, int k)
{
    return (*a >> k) & 1u;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void print_byte (unsigned char a)
{
    for (int i = 7; i>=0; i--)
        printf ("%d", get_bit(&a, i));
    
    printf ("\n");
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void fill_sieve (struct sieve_t* sv)
{
    set_bit ((*sv).mod1, 0);

    for (int i = 7; i * i <= 48 * (*sv).n - 5; i += 6)                         //по 1
        if (!get_bit ((*sv).mod1 + (i - 1) / 48, ((i - 1) / 6) % 8))
            for (int j = i * i; j <= 48 * (*sv).n - 5; j += i)
            {
                if ((j - 1) % 6 == 0)
                    set_bit ((*sv).mod1 + ((j - 1) / 6) / 8, ((j - 1) / 6) % 8);

                if ((j - 5) % 6 == 0)
                    set_bit ((*sv).mod5 + ((j - 5) / 6) / 8, ((j - 5) / 6) % 8);
            }

    for (int i = 5; i * i <= 48 * (*sv).n - 1; i += 6)                          // 2 по 2
        if (!get_bit ((*sv).mod5 + ((i - 5) / 6) / 8, ((i - 5) / 6) % 8))
            for (int j = i * i; j <= 48 * (*sv).n - 1; j += i)
            {
                if ((j - 1) % 6 == 0)
                    set_bit ((*sv).mod1 + ((j - 1) / 6) / 8, ((j - 1) / 6) % 8);

                if ((j - 5) % 6 == 0)
                    set_bit ((*sv).mod5 + ((j - 5) / 6) / 8, ((j - 5) / 6) % 8);
            }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int is_prime (struct sieve_t* sv, unsigned n)
{
    if ((n - 1) % 6 == 0)
        return 1 - get_bit ((*sv).mod1 + (n - 1) / 48, ((n - 1) / 6) % 8);
    
    else if ((n - 5) % 6 == 0)
        return 1 - get_bit ((*sv).mod5 + (n - 5) / 48, ((n - 5) / 6) % 8);

    else 
        return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    struct sieve_t a = {21, calloc(21, sizeof(char)), calloc(21, sizeof(char))};

    fill_sieve (&a);

    printf ("%d", ;
}