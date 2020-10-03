#include <stdio.h>

#define DBG(x, y) printf(#y"\n",x);

//flex

static const int stack_size = 1000;
static double stack[stack_size] = {0};

//flex

void addToStack (double x)
{
        int i = 0;
	
        for(i = *stack; i > 0; i--)
                *(stack + i + 1) = *(stack + i);

        *(stack + 1) = x;

	*stack = *stack + 1;
}

//flex

double getFromStack (void)
{
	double a =*(stack + 1);

	int i = 0;

	for(i = 2;i <= (int)(*stack); i++)
	{
		*(stack + i - 1) = *(stack + i);
	}

	*(stack + (int)(*stack)) = 0;

	*stack = *stack - 1;

	return a;
}

