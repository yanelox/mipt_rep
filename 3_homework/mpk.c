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
    int new_size = poly1.n;

    Poly res = {new_size, (int*) calloc (new_size, sizeof (int))};

    for (unsigned i = 0; i < poly1.n; ++i)
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
    Poly x;
    Poly y;

    Poly A10;
    Poly B10;
    Poly A1B1;
    Poly A0B0;
    Poly AB;
    Poly M;

    int* tmp;

    if (poly1.n < 1000 and poly2.n < 1000)
        return simple_mult (poly1, poly2);

    x = GetFirstPart (poly1);
    y = GetFirstPart (poly2);

    A0B0 = KaratsubaAlg (x, y);

    x = GetSecondPart (poly1);
    y = GetSecondPart (poly2);

    A1B1 = KaratsubaAlg (x, y);

    x = GetFirstPart (poly1);
    y = GetSecondPart (poly1);

    A10 = sum_poly (x, y, 1);

    x = GetFirstPart (poly2);
    y = GetSecondPart (poly2);

    B10 = sum_poly (x, y, 1);

    AB = KaratsubaAlg (A10, B10);

    free (A10.p);
    free (B10.p);

    M = sum_poly (AB, A1B1, -1);

    tmp = M.p;

    M = sum_poly (M, A0B0, -1);

    free (tmp);

    AB = KaratsubaSum (A0B0, M, A1B1);

    free (A1B1.p);
    free (A0B0.p);
    free (M.p);

    return AB;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Poly GetFirstPart (Poly poly)
{
    unsigned half_size = poly.n / 2;

    Poly res = poly;

    res.n = half_size;

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Poly GetSecondPart (Poly poly)
{
    unsigned half_size = poly.n / 2;

    Poly res = poly;

    res.p += half_size;
    res.n = half_size;   

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

Poly KaratsubaSum (Poly first, Poly second, Poly third)
{
    unsigned n = first.n + 1;

    unsigned new_size = 2 * n - 1;

    Poly res = {new_size, (int*) calloc (new_size, sizeof (int))};

    for (unsigned i = 0; i < first.n; i++)
    {
        res.p[i] += first.p[i];

        res.p[i + n / 2] += second.p[i];

        res.p[i + n] += third.p[i];
    }

    return res;
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