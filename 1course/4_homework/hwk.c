#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int str_compare (const char* s1, const char* s2, int len)
{
    assert (s1);
    assert (s2);

    for (int i = 0; i < len; ++i)
        if (tolower (s1[i]) != tolower (s2[i]))
            return 0;

    return 1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void patpreproc(char const * needle, int * needle_lps)
{
    int len = strlen (needle);

    int max = 0;
    int tmp = 0;

    assert (needle);
    assert (needle_lps);
        
    len = strlen (needle);

    for (int i = 1; i <= len; ++i)
    {
        for (int j = i / 2; j >= 0; --j)
        {
            tmp = str_compare (needle, needle + i - j, j);

            if (tmp)
            {
                max = j;
                break;
            }
        }

        needle_lps[i - 1] = max;

        max = 0;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char * strstrci(char const * needle, int const * needle_lps, char const * haystack)
{
    int h_len = 0;
    int n_len = 0;

    int tmp = 1;
    char* res = NULL;

    int i = 0;
    int j = 0;

    assert (needle);
    assert (needle_lps);
    assert (haystack);

    h_len = strlen (haystack);
    n_len = strlen (needle);

    while (i < h_len)
    {
        for (j = i; j < h_len and j - i < n_len; ++j)
            if (tolower (needle[j - i]) != tolower (haystack[j]))
            {
                tmp = 0;
                break;
            }

        if (tmp and j - i == n_len)
        {
            res = (char*) haystack + i;
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

int main ()
{
    const char* s = "Ab";
    const char* s1 = "abracadaBra";

    char* res;

    int len = strlen (s);

    int* mas = (int*) calloc (len, sizeof (int));

    patpreproc (s, mas);

    res = strstrci (s, mas, s1);

    printf ("%s\n", res);

    res = strstrci (s, mas, res + 2);

    printf ("%s\n", res);

    res = strstrci (s, mas, res + 2);

    printf ("%p\n", res);

    free (mas);
}