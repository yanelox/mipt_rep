#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char *strcat_r(char *dest, const char *src, int *bufsz)
{
    int i = 0, j = 0;

    if (strlen(dest) + strlen(src) + 1 > *bufsz)
    {
        dest = (char*) realloc (dest, strlen(dest) + strlen(src) + 1);
        *bufsz = strlen(dest) + strlen(src) + 1;
    }

    i = strlen (dest);

    while (src[j])
    {
        dest[i] = src[j];

        ++i;
        ++j;
    }

    dest[i] = '\0';

    return dest;
}