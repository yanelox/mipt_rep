#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct sieve_t {
  int n;
  unsigned char *mod1;
  unsigned char *mod5;  
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void set_bit (unsigned char* a, int i)
{
    const int K = 6;
    
    int byte_number = i / (K * __CHAR_BIT__);
    int bit_number = (i / K) % __CHAR_BIT__;

    *(a + byte_number) = *(a + byte_number) | (1u << bit_number);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int get_bit (unsigned char *a, int i)
{
    const int K = 6;
    
    int byte_number = i / (K * __CHAR_BIT__);
    int bit_number = (i / K) % __CHAR_BIT__;

    return (*(a + byte_number) >> bit_number) & 1u;
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
    const int K = 6;
    const int mod1_last = __CHAR_BIT__ * K * (*sv).n - 5;
    const int mod5_last = __CHAR_BIT__ * K * (*sv).n - 1;

    set_bit ((*sv).mod1, 1);

    for (int i = 7; i * i <= mod1_last; i += K)                         //по 1
        if (!get_bit ((*sv).mod1, i))
            for (int j = i * i; j <= mod1_last; j += i)
            {
                if ((j - 1) % K == 0)
                    set_bit ((*sv).mod1, j);

                if ((j - 5) % K == 0)
                    set_bit ((*sv).mod5, j);
            }

    for (int i = 5; i * i <= mod5_last; i += K)                          // 2 
        if (!get_bit ((*sv).mod5, i))
            for (int j = i * i; j <= mod5_last; j += i)
            {
                if ((j - 1) % K == 0)
                    set_bit ((*sv).mod1, j);

                if ((j - 5) % K == 0)
                    set_bit ((*sv).mod5, j);
            }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int is_prime (struct sieve_t* sv, unsigned n)
{
    if ((n - 1) % 6 == 0)
        return 1 - get_bit ((*sv).mod1, n);
    
    else if ((n - 5) % 6 == 0)
        return 1 - get_bit ((*sv).mod5, n);

    else 
        return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    unsigned n = 0;

    scanf ("%u", &n);

    n = (n - n % 6 + 6) / 6;
    n = n - n % 8 + 8;

    struct sieve_t a = {n, calloc(n, sizeof(char)), calloc(n, sizeof(char))};

    fill_sieve (&a);
}