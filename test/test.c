#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char * strstrci(char const * haystack, char const * needle)
{
    char* res = NULL;
    unsigned k = 0;

    for (int i = 0; haystack[i]; ++i)
    {
        if (tolower (haystack[i]) == tolower (needle[0]))
            for (int j = 0; needle[j] and haystack[i + j]; ++j)
            {
                if (tolower (haystack[i + j]) != tolower (needle[j]))
                    break;

                k = j + 1;
            }

        if (k == strlen (needle))
        {
            res = (char*) haystack + i;
            break;
        }
    }

    return res;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{  
    fprintf (stdout, "lol\n");
}