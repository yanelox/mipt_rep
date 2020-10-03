#include <stdio.h>
#include <math.h>

int p (int n)
{
    for(int i = 2; i  < sqrt(n) + 1; i++)
        if (n % i == 0)
            return 0;
    
    return 1;
} 

int main ()
{
    int n, a, b, i = 0;
    int max = 0, cur = 0, maxa, maxb;

    scanf ("%d", &n);

    maxa = - n + 1;
    maxb = - n + 1;

    for(a = - n + 1; a < n; a++)
        for(b = - n + 1; b < n; b++)
        {
            i = 0;
            cur = 0;

            while (p(i * i + a * i + b) && (i * i + a * i + b) > 0)
            {
                cur++;
                i++;
            }
            
            if (cur > max)
            {
                maxa = a;
                maxb = b;
                max = cur;
            }
        }   
    
    printf ("%d %d %d", maxa, maxb, max);
}