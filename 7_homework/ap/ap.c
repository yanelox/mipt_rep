#include <stdio.h>

int main()
{
    int n;

    int k = 1;

    k = scanf ("%d", &n);

    for (int i = 2; i * i <= n; ++i)
        if(n % i == 0)
        {
            k = 0;
            break;
        }

    if (k == 1)
    {
        printf ("%d\n", k);
    }
    else
    {
        printf (" %d\n", k);
    }
}