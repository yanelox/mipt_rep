#include <stdio.h>
#include <stdlib.h>

const char END_OF_STR = '\0';
const int SIZE_OF_STR = 100;


void zeroMassive (int* a, int len)
    {
        for (int i = 0; i < len; i++)
            *(a+i) = 0;
    }


void printMassive (int a[], int len)
    {
        printf("\n");

        for (int i = 0; i < len; i++)
            printf("[%d] = %d\n", i, a[i]);
    }


void getMassive (int* a, int len)
    {
        for (int i = 0; i < len; i++)
            scanf("%d", a+i);
    }


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


void copyStr (char* from, char* to)
    {
        int i = 0;

        while ((*(to + i) = *(from + i)) != END_OF_STR)
            i++;
    }


void printStr (char str[])
    {
        int i;

        for (i = 0; i < SIZE_OF_STR - 1 and str[i] != END_OF_STR; i++)
            putchar(str[i]);
    }

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

unsigned setbits (unsigned x, int p, int n, unsigned y)
    {
        return (x & ~(~(~0 << n) << (p - n + 1))) | ((y & ~(~0 << n)) << (p - n + 1));
    }

unsigned getbits (unsigned x, int p, int n)
    {
        return (x >> (p+1-n)) & ~(~0 << n);
    }

unsigned invert (unsigned x, int p, int n)
    {
        return ~(x & (~(~0 << n) << (p - n + 1))) & (x | (~(~0 << n) << (p - n + 1)));
    }

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

int lower (char a)
    {
        return (a >= 'a' and a <= 'z') ? a : a + 'a' - 'A';
    }

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

int strindex (char* a, char t)
    {
        int i = SIZE_OF_STR - 1;

        for (; a[i] != '\0'; i++)
            ;

        for (; a[i] != t and i >= 0; i--)
            ;

        return (i >= 0) ? i : -1;
    }

int compareInt (const void* p1, const void* p2)
    {
        return *(int*) p1 - *(int*) p2;
    }
