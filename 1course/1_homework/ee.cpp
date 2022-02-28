#include<stdio.h>
//test
long long f (long long x, long long y, long long* a, long long* b)
{
	if (x == 0)
	{
		*a = 0;
		*b = 1;
		return y;
	}
	else
	{
		long long a1 = 0;
		long long b1 = 0;
		long long d = f(y % x, x, &a1, &b1);

		*a = b1 - (y / x) * a1;
		*b = a1;
		
		return d;
	}
}

int main()
{
    long long x, y, c, a, b;

	scanf("%lld %lld", &x, &y);
	
	if (x > y)
	{
		c = x;
		x = y;
		y = c;

		c = f(x, y, &b, &a);
	}
	
	else
	{
		c = f(x, y, &a, &b);
	}

	printf("%lld %lld %lld", a, b, c);
}
//aha
