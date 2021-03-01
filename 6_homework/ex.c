#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    float f = 0;

    unsigned* a;

    f = 145.0f / 1024.0f;

    a = (unsigned*) &f;

    printf ("%x\n", *a);
}