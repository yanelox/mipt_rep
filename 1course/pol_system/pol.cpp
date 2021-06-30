#include <stdio.h>           
#include "stack.cpp"

#define DBG(x,y) printf(#y"\n",x);

//flex

int isOperator (char* s);

double StrToDouble (char* s);

int isNumber (char* s);

double calculate (char* s);

//flex

int main (int argc, char* argv[])
{
        int i = 0;

        for(i = 1; i < argc; i++)
        {             
		if(isOperator(argv[i]))
                {
                        addToStack(calculate(argv[i]));
                }
                else if(isNumber(argv[i]))
                {
                        addToStack(StrToDouble(argv[i]));
                }
                else
                {
                        printf("Incorrect input, pls try again\n");
                        break;
                }       
        }

	printf("%.6lf\n", getFromStack());

        return 0;
}

//flex

double StrToDouble (char* s)
{
	double n = 0;

	int i = 0;

	while(s[i] != '.')
	{
		n = n * 10 + s[i] - '0';
		i++;
	}

	int k = 10;

	int j = i + 1;

	for(; j <= i + 6; j++)
	{
		n += (s[i] - '0') / k;
		k *= 10;
	}

	return n;
}

//flex

int isOperator (char* s)
{
        if (*s == 'x' or *s == '+' or *s == '-' or *s == '/')
                return 1;
        else
                return 0;
}

//flex

int isNumber (char* s)
{
	int i = 0;
	
	while (s[i] >= '0' and s[i] <= '9' and s[i] != '.')
		i++;
	
	if (s[i] == '.')
	{
		int j = i + 1;

		for(; j <= i + 6 and s[j] >= '0' and s[j] <= '9'; j ++)
		       ;
		
		if (j == i + 7)
			return 1;
		
		else 
			return 0;	
	}

	else
		return 0;
}

//flex

double calculate (char* s)
{
        double x1 = getFromStack();
        double x2 = getFromStack();
	
	switch(*s)
        {
                case 'x':
                        return x2 * x1;
                        break;
                case '+':
                        return x2 + x1;
                        break;
                case '-':
                        return x2 - x1;
                        break;
                case '/':
                        return x2 / x1;
                        break;
                default:
                        break;
        }

	return 0; 
}
