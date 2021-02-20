#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void fixupstrings(struct namednum *arr, int arrlen) 
{
    char** a = calloc (arrlen, sizeof (char*));
    int n = 0;

    for (int i = 0; i < arrlen; ++i)
    {
        int k = 0;

        for (int j = 0; j < arrlen && a[j] != NULL; ++j)
            if (a[j] == arr[i].name)
                k = 1;

        if (k)
        {
            char* b = arr[i].name;

            arr[i].name = calloc (strlen (b) + 1, sizeof (char));

            strcpy (arr[i].name, b);
        }

        else
        {
            a[n] = arr[i].name;
            ++n;
        }
    }

    free (a);
}
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{

}