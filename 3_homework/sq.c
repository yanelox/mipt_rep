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
    unsigned mid = (low + high) / 2;

    int partititor;

    unsigned left = low;
    unsigned right = high;

    swap (arr + low, arr + mid);

    partititor = arr[mid];

    while (left < right)
    {
        while (arr[left] < partititor and left < right)
            left++;
        
        while (arr[right] > partititor and left < right)
            right--;

        if (left <= right)  
        {
            swap (arr + left, arr + right);

            if (left == mid)
                mid = right;

            else if (right == mid)
                mid = left;

            left++;
            right--;
        }
    }

    return mid;
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