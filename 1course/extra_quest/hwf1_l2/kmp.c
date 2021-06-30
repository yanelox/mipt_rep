#include "head.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int mass_compare (int* s1, int* s2, int len)
{
    assert (s1);
    assert (s2);

    for (int i = 0; i < len; ++i)
        if (s1[i] != s2[i])
            return 0;

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void patpreproc(int* needle, int* needle_lps, int len)
{
    int max = 0;
    int tmp = 0;

    assert (needle);
    assert (needle_lps);
        
    for (int i = 1; i < len; ++i)
    {
        for (int j = (i + 1) / 2; j >= 0; --j)
        {
            tmp = mass_compare (needle, needle + i + 1 - j, j);

            if (tmp)
            {
                max = j;
                break;
            }
        }

        needle_lps[i] = max;

        max = 0;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int strstrci (int* needle, int* needle_lps, int* haystack, int n_len, int h_len)
{
    int tmp = 1;
    int res = 0;

    int i = 0;
    int j = 0;

    assert (needle);
    assert (needle_lps);
    assert (haystack);

    while (i < h_len)
    {
        for (j = i; j < h_len and j - i < n_len; ++j)
            if (needle[j-i] != haystack[j])
            {
                tmp = 0;
                break;
            }

        if (tmp and j - i == n_len)
        {
            res = 1;
            break;
        }

        else
        {
            if (i == j)
                ++i;
            else
                i += j - i - needle_lps[j - i - 1];
        }

        tmp = 1;
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// int main ()
// {
//     int s[]  = {1, 2};
//     int s1[] = {1, 1, 3, 5, 7};

//     int res;

//     int* mas = (int*) calloc (2, sizeof (int));

//     patpreproc (s, mas, 2);

//     res = strstrci (s, mas, s1, 2, 5);

//     printf ("%d\n", res);

//     free (mas);
// }