#include <stdio.h>

void r (int n, int* a)    //записывает в массив первые n чисел фибоначчи
{
	unsigned long long x1 = 1, x2 = 2, tmp;

	int i = 0;

	for(; i < n; i++)
	{
		a[i] = x1;
		
		tmp = x2;
		x2 = x1 + x2;
		x1 = tmp;
	}
}

void p (int* a, int y, int n) //представляет число в виде суммы чисел фибоначчи
{
	int i = n - 1;
	
	int k = 0; 

	for(; i >= 0; i --)
	{
		if (y >= a[i])
		{
			y -= a[i];

			printf("1");

			k++;
		}

		else if (k > 0)
		{
			printf("0");
		}
	}
}

int main ()
{
	int a[45] = {};

	int y = 0;

	scanf("%d", &y);
	
	r(45, a);

	p(a, y, 45);	
}	
