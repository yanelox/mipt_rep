#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char *replace(char *str, char const *from, char const *to)
{
    int n = 0;

    char* res = 0;
    int len = strlen (str);
    char* tmp = str;
    char* f = strstr (str, from);

    while (f)
    {
        n++;

        *f = '\0';

        f = strstr (f + strlen (from), from);
    }

    res = (char*) calloc (len + n * (strlen (to) - strlen (from)) + 1, sizeof (char));

    while (tmp < str + len)
    {
        strcat (res, tmp);

        tmp += strlen (from) + strlen (tmp);

        if (tmp > str + len)
            break;

        strcat (res, to);
    }

    return res;
}