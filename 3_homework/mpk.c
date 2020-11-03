#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
    unsigned n;

    int* p;

} Poly;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void sum_poly               (Poly poly1, Poly poly2, int k, Poly* res);

void simple_mult            (Poly poly1, Poly poly2, Poly* res);

Poly KaratsubaAlg           (Poly poly1, Poly poly2);

void GetFirstPart           (Poly poly, Poly* res);

void GetSecondPart          (Poly poly, Poly* res);

void KaratsubaSum           (Poly first, Poly second, Poly third, Poly* res);

void PrintPoly              (Poly poly);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    Poly poly1;
    Poly poly2;
    Poly res;

    unsigned n1;
    unsigned n2;
    unsigned i;

    scanf ("%u %u", &n1, &n2);

    poly1.p = (int*) calloc (n1, sizeof (int));
    poly2.p = (int*) calloc (n2, sizeof (int));
    poly1.n = n1;
    poly2.n = n2;

    for (i = 0; i < n1; i++)
        scanf ("%d", poly1.p + i);

    for (i = 0; i < n2; i++)
        scanf ("%d", poly2.p + i);


    res = KaratsubaAlg (poly1, poly2);

    PrintPoly (res);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void sum_poly (Poly poly1, Poly poly2, int k, Poly* res)
{
    for (unsigned i = 0; i < poly1.n; ++i)
        res->p[i] = poly1.p[i] + k * poly2.p[i];
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void simple_mult (Poly poly1, Poly poly2, Poly* res)
{   
    for (unsigned i = 0; i < poly1.n; i++)
        for (unsigned j = 0; j < poly2.n; j++)
            res->p[i + j] += poly1.p[i] * poly2.p[j]; 
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Poly KaratsubaAlg (Poly poly1, Poly poly2)
{
    Poly x;
    Poly y;

    Poly A10;
    Poly B10;
    Poly A1B1;
    Poly A0B0;
    Poly AB;
    Poly M;

    if (poly1.n < 100 and poly2.n < 100)
    {
        x.n = poly1.n + poly2.n - 1;
        x.p = (int*) calloc (x.n, sizeof (int));

        simple_mult (poly1, poly2, &x);

        return x;
    }

////

    GetFirstPart (poly1, &x);
    GetFirstPart (poly2, &y);

    A0B0 = KaratsubaAlg (x, y);

////

    GetSecondPart (poly1, &x);
    GetSecondPart (poly2, &y);

    A1B1 = KaratsubaAlg (x, y);

////

    GetFirstPart (poly1, &x);
    GetSecondPart (poly1, &y);

    A10.n = poly1.n / 2;
    A10.p = (int*) calloc (A10.n, sizeof (int));

    sum_poly (x, y, 1, &A10);

////

    GetFirstPart (poly2, &x);
    GetSecondPart (poly2, &y);

    B10.n = poly2.n / 2;
    B10.p = (int*) calloc (B10.n, sizeof (int));

    sum_poly (x, y, 1, &B10);

////

    AB = KaratsubaAlg (A10, B10);

    free (A10.p);
    free (B10.p);

////

    M.n = AB.n;
    M.p = (int*) calloc (M.n, sizeof (int));

    sum_poly (AB, A1B1, -1, &M);

    sum_poly (M, A0B0, -1, &M);

    free (AB.p);

////

    AB.n = 2 * A0B0.n + 1;
    AB.p = (int*) calloc (AB.n, sizeof (int));

    KaratsubaSum (A0B0, M, A1B1, &AB);

    free (A1B1.p);
    free (A0B0.p);
    free (M.p);

    return AB;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void GetFirstPart (Poly poly, Poly* res)
{
    unsigned half_size = poly.n / 2;

    res->n = half_size;
    res->p = poly.p;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void GetSecondPart (Poly poly, Poly* res)
{
    unsigned half_size = poly.n / 2;

    res->n = half_size;
    res->p = poly.p + half_size;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void KaratsubaSum (Poly first, Poly second, Poly third, Poly* res)
{
    unsigned n = first.n + 1;

    for (unsigned i = 0; i < first.n; i++)
    {
        res->p[i] += first.p[i];

        res->p[i + n / 2] += second.p[i];

        res->p[i + n] += third.p[i];
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintPoly (Poly poly)
{
    int i;

    for (i = poly.n - 1; i >= 0; --i)
        if (poly.p[i] != 0)
            break;
    
    for (int j = 0; j <= i; ++j)
        printf ("%d ", poly.p[j]);

    printf ("\n");
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx