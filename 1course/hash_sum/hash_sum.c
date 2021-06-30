#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned long long hash (char* a, size_t len)
{
    unsigned long long sum = 0;

    unsigned long long tmp = 0;

    int n = len;

    for (int i = 0; i < len; i++)
    {
        sum += *(a + i);


        if (i % 2 == 0)
        {
            tmp = (sum & ~(1 >> n)) >> (len - n);

            sum = sum << n;

            sum += tmp;
        }

        else
        {
            tmp = sum & ~(1 << n);

            sum = sum >> n;

            sum += tmp << (len - n);
        }
    }

    return sum;
} 

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    char a[]= {"FISTINR IS 301 BUCKS"};

    printf ("%llX", hash (a, 22));
}