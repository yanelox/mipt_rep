#include<stdio.h>

int main()
{
        long long x, y, x1, y1;

        scanf ("%lld%lld", &x, &y);

        x1 = x;
        y1 = y;

        for(; x != 0; )
        {
                if(x > y)
                {
                        c = x;
                        x = y;
                        y = c;
                }

                y = y % x;

                if(x > y)
                {
                        c = x;
                        x = y;
                        y = c;
                }
        }

        long long d = y;

        long long a = 1, b = 1;

        long long f = a * x1 + b * y1;


}
