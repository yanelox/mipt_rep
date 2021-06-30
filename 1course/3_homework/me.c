#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int majority_element(const int *parr, int len)
{
    int a = 0, b = 0, ka = 0, kb = 0;

    if (len == 1)
        return parr[0];
   
    a = majority_element (parr, len / 2);
    b = majority_element (parr + len / 2, len - len / 2);

    for (int i = 0; i < len; i++)
    {
        if (parr[i] == a)
            ka++;
        
        if (parr[i] == b)
            kb++;
    }

    if (a == -1 and b != -1 and kb > len / 2)
        return b;
    
    if (a != -1 and b == -1 and ka > len / 2)
        return a;

    if (a != -1 and b != -1)
    {
        if (ka > kb)
            return (ka > len / 2) ? a : -1;
        else    
            return (kb > len / 2) ? b : -1;
    }

    return -1;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    int a[] = {3, 3, 4, 2, 4, 4, 2, 4};
    int len = sizeof(a) / sizeof (*a);

    printf ("%d\n", majority_element (a, len));
}