#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct _Decimal {                                                               
    char * a;          // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n       
    unsigned int n;    // наибольшая степень десяти                             
    unsigned int size; // размер выделенной динамической памяти в а (можно это поле не использовать).
};                                                                              
typedef struct _Decimal Decimal;  

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Decimal * half (Decimal * d)
{
    Decimal* res = calloc (1, sizeof (Decimal));
    int i = 0;
    int tmp = 0;
    int tmp_next = 0;
    
    if(d->a[d->n] > '1')    
    {
        res->a = calloc (d->n + 1, sizeof (char));
        res->n = d->n;
        res->size = sizeof (char) * (d->n + 1);

        for (i = d->n; i >= 0; --i)
        {
            tmp = d->a[i] - '0' +  tmp_next;

            tmp_next = tmp % 2 * 10;

            res->a[i] = (tmp / 2) + '0';
        }
    }

    else
    {
        res->a = calloc (d->n, sizeof (char));
        res->n = d->n - 1;
        res->size = sizeof (char) * d->n;

        tmp_next = 10;

        for (i = d->n - 1; i >= 0; --i)
        {
            tmp = d->a[i] - '0' + tmp_next;

            tmp_next = tmp % 2 * 10;

            res->a[i] = (tmp / 2) + '0';
        }
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void dfree (Decimal * d)
{
    free (d->a);
    free (d);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    Decimal* d = calloc (1, sizeof (Decimal));

    d->a = calloc (10, sizeof (char));
    d->n = 9;
    d->a[0] = '0';

    for (int i = 1; i < 10; ++i)
        d->a[i] = 10 - i + '0';

    Decimal* res = half (d);

    for (int i = d->n; i >= 0; --i)
        printf ("%c", d->a[i]);

    printf ("\n");

    for (int i = res->n; i >= 0; --i)
        printf ("%c", res->a[i]);

    printf ("\n");

    dfree (d);
    dfree (res);
}