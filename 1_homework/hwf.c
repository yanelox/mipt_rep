#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void set_bit (unsigned char* c, int k, int b)
{
    *c = *c & ~(1u << k);
    *c = *c | (b << k);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int get_bit (unsigned char c, int k)
{
    return (c >> k) & 1u;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int next_turn (int total, int possible)
{
    int a[100] = {1};
    unsigned char b[15] = {0};
    int x1 = 1, x2 = 2;
    int i = 0, k = 0;

    if (possible >= total)
        return total;

    else 
    {
        int tmp = 0;

        for (i = 1; x2 <= total; i++)
        {
            a[i] = x2;

            tmp = x1;
            x1 = x2;
            x2 += tmp;
            
            k = i;
        }

        for (i = k; i>=0; i--)
            if (total >= a[i])
            {
                total -= a[i];

                set_bit (b + i / 8, i % 8, 1);
            }

        for (i = 0; i <= k; i++)
            if (get_bit(b[i/8], i % 8) and a[i] <= possible)
                return a[i];

        return 1;    
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    printf ("\n%d", next_turn(10, 9));
}