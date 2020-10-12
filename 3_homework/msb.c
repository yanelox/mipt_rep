#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int higher_bit (unsigned long long n)
{
    int k = 0;

    if (n == 0)
        return -1;

    while (n > 0)
    {
        n = n >> 1;
        k++;
    }

    return k - 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    unsigned long long a;

    scanf ("%llu", &a);

    printf ("%d", higher_bit (a));
}