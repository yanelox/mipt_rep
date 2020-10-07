#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const int n = 40;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void fill_f (int* a)
{
    int x1 = 1, x2 = 2, tmp = 0;

    a[0] = 1;

    for (int i = 1; i < n; i++)
    {
        a[i] = x2;

        tmp = x2;
        x2 += x1;
        x1 = tmp;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void set_bit (unsigned char* c, int k, int b)
{
    *(c + k / 8) = *(c + k / 8) & ~(1u << (k % 8));
    *(c + k / 8) = *(c + k / 8) | (b << (k % 8));
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int get_bit (char* c, int k)
{
    return (*(c + k / 8) >> (k % 8)) & 1u;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void to_fb_sys (char* b, int total, int* a)
{
    for (int i = n - 1; i >= 0; i--)
        if (total >= a[i])
        {
            total -= a[i];

            set_bit (b, a[i], 1);
        }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int next_turn (int total, int possible, int* a)
{
    unsigned char b = callo;
    int i = 0, k = 0;

    if (possible >= total)
        return total;

    else 
    {
        to_fb_sys (b, total, a);

        for (i = 0; i <= k; i++)
            if (get_bit(b, i) and a[i] <= possible)
                return a[i];

        return 1;    
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int a[n];

    fill_f(a);

    printf ("\n%d", next_turn(10, 9, a));
}