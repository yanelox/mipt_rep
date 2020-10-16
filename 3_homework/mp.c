#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define or ||
#define and &&

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct Poly 
{
    unsigned n;

    int* p;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct Poly mult_p (struct Poly p1, struct Poly p2)
{
    struct Poly res = {p1.n + p2.n - 1, (int*) calloc (p1.n + p2.n - 1, sizeof(int))};

    int tmp = 0;

    for (int i = 0; i < p1.n + p2.n - 1; i++)
    {
        tmp = 0;

        for (int j = 0; j <= i; j++)
            if (j < p1.n and i - j < p2.n)
                tmp += *(p1.p + j) * *(p2.p + i - j);            

        *(res.p + i) = tmp;
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n1 = 0, n2 = 0, i = 0;

    struct Poly p1 = {};
    struct Poly p2 = {};
    struct Poly res = {};

    scanf ("%d %d", &n1, &n2);

    p1.n = n1;
    p1.p = calloc (n1, sizeof (int));
    p2.n = n2;
    p2.p = calloc (n2, sizeof (int));

    for (i = 0; i < n1; i++)
        scanf ("%d", p1.p + i);

    for (i = 0; i < n2; i++)
        scanf ("%d", p2.p + i);

    res = mult_p (p1, p2);

    for (i = res.n - 1; i >= 0; i--)
        if (*(res.p + i) != 0)
            break;
    
    for (int j = 0; j <= i; j++)
        printf ("%d ", *(res.p + j));
}