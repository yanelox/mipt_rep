#include <stdio.h>

int smth_str (unsigned char a)
{
    int k = 0;

    while (a > 0)
    {
        a = a & (a - 1);

        k++;
    }

    return k;
}

int arrpopcount(const unsigned char *parr, int len)
{
    int k = 0;

    for (int i = 0; i < len; i++)
        k += smth_str ((unsigned char) parr[i]);

    return k;
}