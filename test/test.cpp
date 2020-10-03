#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <locale.h>

//-----------------------------------------------------------------------------

#define swap(t, x, y) t c = x; x = y; y = c;

#define max(a,b) ((a > b) ? a : b)

//-----------------------------------------------------------------------------


const char END_OF_STR = '\0';
const int SIZE_OF_STR = 100;

//-----------------------------------------------------------------------------

void zeroMassive (int* a, int len)
{
	for (int i = 0; i < len; i++)
     		*(a+i) = 0;
}

//-----------------------------------------------------------------------------

void printMassive (int a[], int len)
{
        printf("\n");

        for (int i = 0; i < len; i++)
           	printf("[%d] = %d\n", i, a[i]);
}

//-----------------------------------------------------------------------------

void getMassive (int* a, int len)
{
        for (int i = 0; i < len; i++)
            	scanf("%d", a+i);
}

//-----------------------------------------------------------------------------

void reverseStr (char from[], char* to)
{
        int i;

        for (i = 0; i < SIZE_OF_STR and from[i] != END_OF_STR; i++)
            	;

        int cur_len = i;

        for (i = 0; i < cur_len; i++)
        {
         	*(to + i) = from[cur_len - 1 - i];
        }

        *(to + cur_len) = END_OF_STR;
}

//-----------------------------------------------------------------------------

void getStr (char* str)
    {
        int cur,i;

        for (i = 0; i < SIZE_OF_STR - 1 and (cur = getchar()) != EOF and cur != '\n'; i++)
            str[i] = cur;

        if (cur == 'n')
        {
            str[i] = cur;
            i++;
        }

        str[i] = END_OF_STR;
    }

//-----------------------------------------------------------------------------

void copyStr (char* from, char* to)
    {
        int i = 0;

        while ((*(to + i) = *(from + i)) != END_OF_STR)
            i++;
    }

//-----------------------------------------------------------------------------

void printStr (char str[])
    {
        int i;

        for (i = 0; i < SIZE_OF_STR - 1 and str[i] != END_OF_STR; i++)
            putchar(str[i]);
    }

//-----------------------------------------------------------------------------

int htol (char* a)
    {
        int x = 0, k = 1, c = 0;

        for (int i = 0; a [i] != '\n'; i++)
            c = i;

        for (int i = c; i > 1; i--)
        {
            if (a [i] >= 'a' and a [i] <= 'f')
                x += (a [i] - 'a' + 10) * k;

            else if (a [i] >= 'A' and a [i] <= 'F')
                x += (a [i] - 'A' + 10) * k;
            else if (a [i] >= '0' and a [i] <= '9')
                x += (a [i] - '0') * k;

            k *= 16;


        }

        return x;
    }

//-----------------------------------------------------------------------------

unsigned setbits (unsigned x, int p, int n, unsigned y)
    {
        return (x & ~(~(~0 << n) << (p - n + 1))) | ((y & ~(~0 << n)) << (p - n + 1));
    }

//-----------------------------------------------------------------------------

unsigned getbits (unsigned x, int p, int n)
    {
        return (x >> (p+1-n)) & ~(~0 << n);
    }

//-----------------------------------------------------------------------------

unsigned invert (unsigned x, int p, int n)
    {
        return ~(x & (~(~0 << n) << (p - n + 1))) & (x | (~(~0 << n) << (p - n + 1)));
    }

//-----------------------------------------------------------------------------

unsigned rightrot (unsigned x, int n)
    {
        unsigned a = x, b = x;
        int k = 0;

        while(x != 0)
            {
            k++;
            x /= 2;
            }

        return (a >> n) | (b & ~(~0 << n)) << (k - n);
    }

//-----------------------------------------------------------------------------

int bitcount (unsigned x)
    {
        unsigned c = x;
        int k = 0;

        while (x != 0)
        {
            c = x;
            x &= c - 1;
            k ++;
        }

        return k;
    }

//-----------------------------------------------------------------------------

int lower (char a)
    {
        return (a >= 'a' and a <= 'z') ? a : a + 'a' - 'A';
    }

//-----------------------------------------------------------------------------

void itob (char* a, int n, int b)
    {
        int i = 0;

        while (n != 0)
        {
            if (n % b < 10)
                a [i] = '0'  + (n % b);
            else
                a [i] = 'a' + (n % b) - 10;

            n /= b;
            i++;
        }

        a [i] = END_OF_STR;

        char help [SIZE_OF_STR];

        reverseStr (a, help);

        for(int i = 0; help [i] != END_OF_STR; i++)
        {
            a [i] = help [i];
        }
    }

//-----------------------------------------------------------------------------

int strindex (char* a, char t)
    {
        int i = SIZE_OF_STR - 1;

        for (; a[i] != '\0'; i++)
            ;

        for (; a[i] != t and i >= 0; i--)
            ;

        return (i >= 0) ? i : -1;
    }

//-----------------------------------------------------------------------------

int compareInt (const void* p1, const void* p2)
    {
        return *(int*) p1 - *(int*) p2;
    }

//-----------------------------------------------------------------------------

bool isLetter (char a)
    {
        return ((a >= 'a' and a <= 'z') or
                (a >= 'A' and a <= 'Z' )) ? 1 : 0;
    }

//-----------------------------------------------------------------------------

char toLower (char a)
    {
        return (a >= 'A' and a <= 'Z') ? a - 'A' + 'a' : a;
    }

//-----------------------------------------------------------------------------

bool maxStr (char s1 [], char s2 [])
    {
        int i = 0, j =  0;

        int cur_let1 = s1 [i];
        int cur_let2 = s2 [j];


        while (cur_let1 != '\n' and
               cur_let2 != '\n')
        {
            if ( isLetter (cur_let1) and                        // if current symbols
                 isLetter (cur_let2) )                          // in both string is letters
            {
                cur_let1 = toLower (cur_let1);                  // turns copies of both symbols
                cur_let2 = toLower (cur_let2);                  // to lowercase

                if (cur_let1 != cur_let2)
                {
                    return (cur_let1 < cur_let2) ? 1 : 0;
                }
            }

            else if (isLetter (cur_let1) and                    // if symbol of second string is not letter,
                    !isLetter (cur_let2) )                      // we must skip him, but stay at current
            {                                                   // symbol in first string
                i--;
            }
            else if (!isLetter (cur_let1) and                   // analogically, but for first string
                     isLetter (cur_let2) )
            {                                                   // if symbols in both string are not letters
                j--;                                            // we must skip both symbols, so we do
            }                                                   // // nothing

            i++;
            j++;

            cur_let1 = s1 [i];
            cur_let2 = s2 [j];
        }

        if (cur_let1 == '\n')
            return 1;
        else
            return 0;
    }

//-----------------------------------------------------------------------------

int gcd (int x, int y)
    {
        int q;

        if(y > x)
            return gcd(y, x);

        assert(y > 0);

        q = x % y;

        if(q == 0)
            return y;

        return gcd (y ,q);
    }

//-----------------------------------------------------------------------------

bool find_in (char a, char* delim)
{
	int i = 0;

	while (*(delim + i) != END_OF_STR)
	{
		if (*(delim + i) == a)
			return 1;
		i++;
	}
	
	return 0;
}	

//flex

char* p_strtok = 0;
char  m_strtok[] = {"/0"};

char* tokStr (char* str, char* delim)
{
        int j = 0;

        if (str != NULL)
                p_strtok = str;

        while(!find_in(*(p_strtok+j), delim))
        {
                m_strtok[j] = *(p_strtok + j);

                j++;
        }
	
	m_strtok[j] = END_OF_STR;

	return m_strtok;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void IntSortingSwap (int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void IntQuickSort (int* mass, int size)
{
    int i = 0;
    int j = size - 1;

    int mid = mass[size / 2];

    do
    {
        while (mass[i] < mid)
            i++;

        while (mass[j] > mid)
            j--;

        if (i <= j)
        {
            int hlp = mass[i];
            mass[i] = mass[j];
            mass[j] = hlp;

            i++;
            j--;
        }
    }

    while (i <= j);

    if (j > 0)
        IntQuickSort (mass, j + 1);
    
    if (i < size)
        IntQuickSort (mass + i, size - i);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    int a [10];

    for (int i = 0; i < 10; i++)
        a [i] = rand() % 20;

    printMassive (a, 10);

    IntQuickSort (a, 10);

    printMassive (a, 10);
}	
