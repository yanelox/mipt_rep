#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct sieve_t {
  int n;
  unsigned char *mod1;
  unsigned char *mod5;  
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void set_bit (unsigned char* a, int i);

int get_bit (unsigned char *a, int i);

void print_byte (unsigned char a);

void fill_sieve (struct sieve_t* sv);

int is_prime (struct sieve_t* sv, unsigned n);

int naive_alg (int n);

int test_func (int n)

int finding_in_sieve (int n);

int calculate_ones_func (char a)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    
}

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
    for (int i = 7; i >= 0; i--)
        printf ("%d", get_bit(&a, 6 * i));
    
    printf ("\n");
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void fill_sieve (struct sieve_t* sv)
{
    const int K = 6;
    const int mod1_last = __CHAR_BIT__ * K * sv->n - 5;
    const int mod5_last = __CHAR_BIT__ * K * sv->n - 1;

    set_bit (sv->mod1, 1);

    for (int i = 7; i * i <= mod1_last; i += K)                         //по 1
        if (!get_bit (sv->mod1, i))
            for (int j = i * i; j <= mod1_last; j += i)
            {
                if ((j - 1) % K == 0)
                    set_bit ((sv->mod1, j);

                if ((j - 5) % K == 0)
                    set_bit (sv->mod5, j);
            }

    for (int i = 5; i * i <= mod5_last; i += K)                          // 2 
        if (!get_bit (sv->mod5, i))
            for (int j = i * i; j <= mod5_last; j += i)
            {
                if ((j - 1) % K == 0)
                    set_bit (sv->mod1, j);

                if ((j - 5) % K == 0)
                    set_bit (sv->mod5, j);
            }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int is_prime (struct sieve_t* sv, unsigned n)
{
    if ((n - 1) % 6 == 0)
        return 1 - get_bit (sv->mod1, n);
    
    else if ((n - 5) % 6 == 0)
        return 1 - get_bit ((sv->mod5, n);

    else 
        return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int naive_alg (int n)
{
    int k = 0, z = 0, i = 0;

    for (i = 2; k < n; i++)
    {
        z = 0;

        for (int j = 2; j < i; j++)
            if (i % j == 0)
            {
                z++;
                break;
            }

        if (!z)
            k++;
    }

    return i - 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int test_func (int n)
{
    n = n / 6;
    n = n / 8 + 1;

    struct sieve_t a = {n, calloc(n, sizeof(char)), calloc(n, sizeof(char))};

    fill_sieve (&a);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int finding_in_sieve (int n, struct sieve_t* a)
{
    int tmp = 0, i = 0;

    while (tmp < n)
    {
        tmp += 16 - calculate_ones_func (a->mod1[i]) - calculate_ones_func (a->mod5[i]);

        i++;
    }

    i--;

    tmp -= 16 - calculate_ones_func (a->mod1[i]) - calculate_ones_func (a->mod5[i]);

    
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int calculate_ones_func (char a)
{
    int c = 0;

    while (a)
    {
        c++;
        
        a = a & (a - 1);
    }

    return c;
}