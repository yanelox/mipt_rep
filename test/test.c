#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    char* s = (char*) calloc (100, sizeof (char));

    char* delim = (char*) calloc (100, sizeof (char));

    char* tmp = (char*) calloc (100, sizeof (char));

    strcpy (s, "100 200\0");
    strcpy  (delim, " \n");

    printf ("%s\n", s);

    char* lexem  = strtok (s, delim);

    printf ("%s\n", lexem);

    lexem = strtok (NULL, delim);

    printf ("%s\n", lexem);

    strcpy (tmp, lexem);

    strcat (s, " ");
    strcat (s, tmp);

    printf ("%s\n", s);

    free (s);
    free (delim);
    free (tmp);
}