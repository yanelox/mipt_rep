#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum game_return_values
{
    WIN_VALUE = 42,
    LOSE_VALUE = -42
};

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

int get_bit (unsigned char* c, int k)
{
    return (*(c + k / 8) >> (k % 8)) & 1u;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void to_fb_sys (unsigned char* b, int total, int* a)
{
    for (int i = n - 1; i >= 0; i--)
        if (total >= a[i])
        {
            total -= a[i];

            set_bit (b, i, 1);
        }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int next_turn (int total, int possible, int* a)
{
    unsigned char* b = (unsigned char*) calloc (n / __CHAR_BIT__ + 1, sizeof(unsigned char));
    int i = 0, k = n - 1;

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

int enemy_step (int total, int possible)
{
    int step = (int) rand() % possible;

    while (step == 0) 
        step = (int) rand() % possible;

    return step;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int game (int total, int* a)
{
    int possible = total - 1;

    while (total > 0)
    {
        possible = 2 * next_turn (total, possible, a);

        total -= possible / 2;

        if (total == 0)
            return WIN_VALUE;

        possible = 2 * enemy_step (total, possible);

        total -= possible / 2;
    }

    return LOSE_VALUE;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int a[n], res = 0, count_loses = 0;

    fill_f(a);

    for (int c = 10; c <= 1000; c++)
    {
        res = game (c, a);

        if (res == LOSE_VALUE)
            count_loses++;
    }

    printf ("%d\n", count_loses);
}