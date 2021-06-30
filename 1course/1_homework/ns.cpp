#include <stdio.h>

#define DBG(x, y) printf(#y, x);

int f (unsigned long long x, int y, int* a)
{
	int i = 0;

	while (x != 0)
	{
		*(a + i) = (int) (x % y);

		x = x / y;

		i++;
	}

	return i;
}

int main ()
{
	int a[100] = {0};
	
	int n = 0, y = 0, i = 0;

	unsigned long long x;

	scanf ("%llu %d", &x, &y);

	n = f(x, y, a);

	for (i = n - 1; i >= 0; i--)
		DBG(*(a + i), %d);
}
