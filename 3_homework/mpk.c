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

Poly sum_poly               (Poly poly1, Poly poly2, int k);

Poly simple_mult            (Poly poly1, Poly poly2);

Poly KaratsubaAlg           (Poly poly1, Poly poly2);

Poly GetFirstPart           (Poly poly);

Poly GetSecondPart          (Poly poly);

Poly KaratsubaSum           (Poly first, Poly second, Poly third);

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

Poly sum_poly (Poly poly1, Poly poly2, int k)
{
    unsigned new_size = (poly1.n > poly2.n) ? poly1.n : poly2.n;

    Poly res = {new_size, (int*) calloc (new_size, sizeof (int))};

    for (unsigned i = 0; i < new_size; ++i)
        res.p[i] = poly1.p[i] + k * poly2.p[i];

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Poly simple_mult (Poly poly1, Poly poly2)
{
    unsigned new_size = poly1.n + poly2.n - 1;

    Poly res = {new_size, (int*) calloc (new_size, sizeof (int))};

    for (unsigned i = 0; i < poly1.n; i++)
        for (unsigned j = 0; j < poly2.n; j++)
            res.p[i + j] += poly1.p[i] * poly2.p[j]; 
    
    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Poly KaratsubaAlg (Poly poly1, Poly poly2)
{
    Poly A0;
    Poly A1;
    Poly B0;
    Poly B1;

    Poly A1B1;
    Poly A0B0;
    Poly A10;
    Poly B10;
    Poly AB;
    Poly MiddlePart;

    Poly res;

    if (poly1.n < 3 and poly2.n < 3)
        return simple_mult (poly1, poly2);

    A0 = GetFirstPart   (poly1);
    A1 = GetSecondPart  (poly1);
    B0 = GetFirstPart   (poly2);
    B1 = GetSecondPart  (poly2);

    A1B1 = KaratsubaAlg (A1, B1);
    A0B0 = KaratsubaAlg (A0, B0);

    A10 = sum_poly (A1, A0, 1);
    B10 = sum_poly (B1, B0, 1);

    free (A0.p);
    free (A1.p);
    free (B0.p);
    free (B1.p);

    AB = KaratsubaAlg (A10, B10);

    free (A10.p);
    free (B10.p);

    MiddlePart = sum_poly (AB, A1B1, -1);
    MiddlePart = sum_poly (MiddlePart, A0B0, -1);

    res = KaratsubaSum (A0B0, MiddlePart, A1B1);

    free (A1B1.p);
    free (A0B0.p);
    free (AB.p);
    free (MiddlePart.p);

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Poly GetFirstPart (Poly poly)
{
    unsigned half_size = poly.n / 2;

    Poly res = {half_size, (int*) calloc (half_size, sizeof (int))};

    for (unsigned i = 0; i < half_size; i++)
        res.p[i] = poly.p[i];

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Poly GetSecondPart (Poly poly)
{
    unsigned half_size = poly.n - poly.n / 2;

    Poly res = {half_size, (int*) calloc (half_size, sizeof (int))};

    for (unsigned i = 0; i < half_size; i++)
        res.p[i] = poly.p[i + poly.n / 2];   

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Poly KaratsubaSum (Poly first, Poly second, Poly third)
{
    unsigned new_size = first.n + second.n + third.n;

    Poly res = {new_size, (int*) calloc (new_size, sizeof (int))};

    for (unsigned i = 0; i < new_size; i++)
    {
        if (i < first.n)
            res.p[i] = first.p[i];

        if (i >= first.n and i < first.n + second.n)
            res.p[i] = second.p[i - first.n];

        if ( i >= first.n + second.n)
            res.p[i] = third.p[i - first.n - second.n];
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintPoly (Poly poly)
{
    unsigned i;

    for (i = poly.n - 1; i >= 0; --i)
        if (poly.p[i] != 0)
            break;
    
    for (unsigned j = 0; j <= i; ++j)
        printf ("%d ", poly.p[j]);

    printf ("\n");
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
