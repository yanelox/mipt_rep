#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct
{
    int* res;

    int add;
    int sub;
    int chg;

    int len;

    char* s1;
    char* s2;

} data;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int K (data data, int i, int j)
{
    if (data.s1[i - 1] == data.s2[j - 1])
        return 0;

    return 2;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int D (data data, int i, int j)
{
    int a, b, c;

    if (i == 0)
    {
        return *(data.res + j - 1) + data.add;
    }

    if (j == 0)
    {
        return *(data.res + i * data.len) + data.sub;
    }

    a = *(data.res + i * data.len + j - 1) + data.add;
    b = *(data.res + (i - 1) * data.len + j) + data.sub;
    c = *(data.res + (i - 1) * data.len + j - 1) + K (data, i, j);

    if (b < c)
        if (a < b)
            return a;
        else
            return b;
    else
        if (a < c)
            return a;
        else
            return c;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int add, sub, chg, len1, len2;

    int* res;

    char* s1;
    char* s2;

    data data;

    scanf ("%d%d%d%d", &add, &sub, &chg, &len1);

    s1 = (char*) calloc (len1 + 1, sizeof (char));

    scanf ("%s %d", s1, &len2);

    s2 = (char*) calloc (len2 + 1, sizeof (char));

    scanf ("%s", s2);

    res = (int*) calloc ((len1 + 1) * (len2 + 1), sizeof (int));

    data.res = res;
    data.add = add;
    data.sub = sub;
    data.chg = chg;
    data.len = len2 + 1;
    data.s1  = s1;
    data.s2  = s2;

    for (int i = 0; i <= len1; ++i)
        *(res + i * data.len) = i;

    for (int j = 0; j <= len2; ++j)
        *(res + j) = j;

    for (int i = 1; i <= len1; ++i)
        for (int j = 1; j <= i and j <= len2; ++j)
            *(res + (i - j + 1) * data.len + j) = D (data, i - j + 1, j);

    for (int j = 2; j <= len2; ++j)
        for (int i = len1; i > 0 and j - i + len1 <= len2; --i)
            *(res + i * data.len + j - i + len1) = D (data, i, j - i + len1);

    printf ("%d\n", *(res + len1 * len2 + len1 + len2));

    free (s1);
    free (s2);
    free (res);
}