#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define and &&
#define or ||

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void swap (int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned partition(int *arr, unsigned low, unsigned high)
{
    unsigned last = low;

    for (unsigned i = low; i <= high; ++i)
        if (arr[i] < arr[low])
            swap (arr + i, arr + ++last);

    swap (arr + low, arr + last);

    return last;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void PrintMass (int arr[], int len)
{
    for (int i = 0; i < len; i++)
        printf ("%d ", arr[i]); 

    printf ("\n");   
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    int arr[] = {2, 1, 3};

    unsigned mid = partition (arr, 0, 2);

    PrintMass (arr, 3);
}