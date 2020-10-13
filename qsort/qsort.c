#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int SwapE (int* a, int* b)
{   
    if (a == NULL or b == NULL)
        return -1;

    int c = *a;
    *a = *b;
    *b = c;

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int Partition (int* mass, int low, int high)
{
    int sup_el = mass[(low + high) / 2];

    int left = low - 1;
    int right = high + 1;

    for (;;)
    {
        do
            left++;
        while (mass[left] < sup_el);

        do
            right--;
        while (mass[right] > sup_el);
        
        if (left >= right)
            return right;

        SwapE (mass + left, mass + right);

        left++;
        right--;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int QuickSort (int* mass, unsigned size)
{
    int left = 0, right = size - 1;
    
    if (left < right)
    {
        int p = Partition (mass, left, right);

        QuickSort (mass, p + 1);

        QuickSort (mass + p + 1, size - p - 1);
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int a[] = {1, 3, 9, 4, 5, 4, 11, 13, 2};

    QuickSort (a, 9);

    for (int i = 0; i < 9; i++)
        printf ("%d ", a[i]);
}