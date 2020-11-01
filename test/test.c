#include <stdio.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int n, tmp_n;
    int x;
    int y;

    scanf ("%d", &n);

    tmp_n = (n > 0) ? n : -n;

    x = tmp_n;
    y = 0;

    while (((x & y) != 0) or (((x | y) & ((x | y) >> 1)) != 0))
    {
        x++;
        y++;
    }

    if (n > 0)
        printf ("%d %d\n", x, y);
    
    else   
        printf ("%d %d\n", y, x);
}