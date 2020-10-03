#include <stdio.h>

unsigned long long gcd (unsigned long long x, unsigned long long y)
{
	unsigned long long c;
	
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

	return y;
}

unsigned long long lcm (unsigned long x, unsigned long long y)
{
	return x * y / gcd(x, y);
}

int main()
{
	unsigned long long n;

	unsigned long long a = 2, b = 3;

	scanf("%llu", &n);

	for(; b<=n; b++)
	{
		a = lcm (a, b);
	}

	printf("%llu", a);
}
